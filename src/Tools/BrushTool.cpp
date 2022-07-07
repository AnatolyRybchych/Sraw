#include "BrushTool.hpp"
#include "../DrawImage.hpp"
#include "../ResourceProvider.hpp"

#include <math.h>

static int distancei(int x1, int y1, int x2, int y2){
    int x = x2 - x1;
    int y = y2 - y1;
    return (int)(sqrt(x*x + y*y) + 0.5);
}

void BrushTool::ClearBuffer() const noexcept{
    frameBuffer->Bind();
    frameBuffer->AttachTexture2D(buffer->GetGLID());
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    frameBuffer->Unbind();
}

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

void BrushTool::OnDraw() const noexcept{
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    DrawImage::GetRenderer().Draw(buffer->GetGLID());
    DrawCircle(prevX, prevY);
}

void BrushTool::OnDrawCommit() noexcept{
    DrawImage::GetRenderer().Draw(buffer->GetGLID());
}

void BrushTool::BrushTool::OnResize(int cx, int cy) noexcept{
    Texture *newBuffer = new Texture(cx, cy);
    frameBuffer->AttachTexture2D(newBuffer->GetGLID());
    frameBuffer->Bind();
    DrawImage::GetRenderer().Draw(buffer->GetGLID());
    frameBuffer->Unbind();

    buffer = std::unique_ptr<Texture>(newBuffer);
}

bool BrushTool::OnMouseMove(int x, int y) noexcept{
    if(isMouseDown){
        frameBuffer->Bind();
        frameBuffer->AttachTexture2D(buffer->GetGLID());

        int points = distancei(prevX, prevY, x, y);
        int distanceX = x - prevX;
        int distanceY = y - prevY;
        for(int i = 0; i <= points; i++){
            DrawCircle(
                prevX + (i / (float)points) * (float)distanceX,
                prevY + (i / (float)points) * (float)distanceY
            );
        }

        frameBuffer->Unbind();
        prevX = x;
        prevY = y;
        return true;
    }
    prevX = x;
    prevY = y;
    return true;
}

bool BrushTool::OnLMouseDown(int x, int y) noexcept{
    isMouseDown = true;
    prevX = x;
    prevY = y;
    OnMouseMove(x + 1, y);
    return true;
}

bool BrushTool::OnLMouseUp(int x, int y) noexcept{
    if(isMouseDown){
        OnMouseMove(x, y);
        isMouseDown = false;

        Commit();
        ClearBuffer();
        prevX = x;
        prevY = y;
        return true;
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

BrushTool::BrushTool(int cx, int cy, CommitHandler &commitHandler, ColorPaletTool &colorPalet) noexcept: 
    DrawingTool(cx, cy, commitHandler),
    colorPalet(colorPalet),
    buffer(new Texture(cx, cy)),
    frameBuffer(new Framebuffer()){

    ClearBuffer();

    prog = BuildShaderProgram(
        ResourceProvider::GetProvider().GetDrawCircleVertex().c_str(),
        ResourceProvider::GetProvider().GetDrawCircleFragment().c_str()
    );

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
