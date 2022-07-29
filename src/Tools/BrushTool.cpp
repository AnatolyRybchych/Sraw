#include "BrushTool.hpp"
#include "../DrawImage.hpp"
#include "../ResourceProvider.hpp"
#include <stdbool.h>
#include "../Basics.hpp"

#include <math.h>

void BrushTool::DrawCircle(int x, int y) const noexcept{
    glUseProgram(prog);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(vertex_pPos);
    
    glUniform3f(colorPos, colorPalet.GetRed(), colorPalet.GetGreen(), colorPalet.GetBlue());
    glUniform2f(posPos, (x / (float)GetViewportWidth() - 0.5) * 2.0, (0.5 - y / (float)GetViewportHeight()) * 2.0);
    glUniform2f(viewportPos, (float)GetViewportWidth(),(float)GetViewportHeight());
    glUniform1f(powerPos, power);
    glUniform1f(scalePos, scale);

    glVertexAttribPointer(vertex_pPos, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(vertex_pPos);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}

void BrushTool::DrawLine(int x1, int y1, int x2,  int y2) const noexcept{
    float step = (1.0 - 1.0 / (distance2(x1, y1, x2, y2) + 1.0)) * scale * 0.5;
    for(float progress = 0.0; progress < 1.0; progress += step){
        DrawCircle(lerpi(x1, x2, progress), lerpi(y1, y2, progress));
    }
}

void BrushTool::OnDraw() const noexcept{
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    DrawImage::GetRenderer().Draw(GetCommitBuffer().GetGLID());
    DrawCircle(prevX, prevY);
}

bool BrushTool::OnMouseMove(int x, int y) noexcept{
    if(isMouseDown){
        BindFramebuffer(GetCommitBuffer().GetGLID());
        DrawLine(prevX, prevY, x, y);
        UnbindFramebuffer();
    }
    prevX = x;
    prevY = y;
    return true;
}

bool BrushTool::OnLMouseDown(int x, int y) noexcept{
    isMouseDown = true;
    prevX = x;
    prevY = y;
    BindFramebuffer(GetCommitBuffer().GetGLID());
    DrawCircle(x, y);
    UnbindFramebuffer();
    return true;
}

bool BrushTool::OnLMouseUp(int x, int y) noexcept{
    if(isMouseDown){
        isMouseDown = false;
        Commit();
        ClearCommitBuffer();
    }
    prevX = x;
    prevY = y;
    return true;
}

bool BrushTool::OnKeyDown(int vkCode, int repeat) noexcept{
    switch (vkCode)
    {
    case VK_OEM_6:{
        scale *= 1.0 + scaleIncrement;
        if(scale > scaleMax) scale = scaleMax;
    } return true;
    case VK_OEM_4:{
        scale *= 1.0 - scaleIncrement;
        if(scale < scaleMin) scale = scaleMin;  
    } return true;
    case VK_OEM_1:{
        power = pow(power, 1.1);
        if(power < powerMin) power = powerMin;  
    } return true;
    case VK_OEM_7:{
        power = pow(power, 0.9);
        if(power > powerMax) power = powerMax;  
    } return true;
    
    default: return false;
    }
}

bool BrushTool::OnKeyUp(int vkCode) noexcept{
    return false;
}

bool BrushTool::OnTextInput(std::wstring str) noexcept{
    return false;
}

bool BrushTool::OnScrollUp() noexcept{
    scale *= 1.0 + scaleIncrement;
        if(scale > scaleMax) scale = scaleMax;
    return true;
}

bool BrushTool::OnScrollDown() noexcept{
    scale *= 1.0 - scaleIncrement;
        if(scale < scaleMin) scale = scaleMin;  
    return true;
}

BrushTool::BrushTool(int cx, int cy, CommitHandler &commitHandler, const Texture &bg, ColorPaletTool &colorPalet) noexcept: 
    DrawingTool(cx, cy, commitHandler, bg),
    colorPalet(colorPalet){

    prog = ResourceProvider::GetProvider().GetDrawCircleProgram();

    vertex_pPos = glGetAttribLocation(prog, "vertex_p");
    colorPos = glGetUniformLocation(prog, "color");
    posPos = glGetUniformLocation(prog, "pos");
    viewportPos = glGetUniformLocation(prog, "viewport");
    powerPos = glGetUniformLocation(prog, "power");
    scalePos = glGetUniformLocation(prog, "scale");
    
    float vertices[] = {
        -1, 1, 1, -1, 1, 1,
        -1, 1, 1, -1, -1, -1
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

BrushTool::~BrushTool() noexcept{
    glDeleteProgram(prog);
    glDeleteBuffers(1, &VBO);
}
