#include "BrushTool.hpp"
#include "../DrawImage.hpp"
#include "../ResourceProvider.hpp"
#include <stdbool.h>
#include "../Basics.hpp"

#include <math.h>

void BrushTool::DrawCircle(const Coords &pos) const noexcept{
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glUseProgram(prog);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(vertex_pPos);
    
    glUniform3f(colorPos, colorPalet.GetRed(), colorPalet.GetGreen(), colorPalet.GetBlue());
    glUniform2f(posPos, pos.GetXGl(), pos.GetYGl());
    glUniform2f(viewportPos, (float)GetViewportWidth(),(float)GetViewportHeight());
    glUniform1f(powerPos, power);
    glUniform1f(scalePos, scale);

    glVertexAttribPointer(vertex_pPos, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(vertex_pPos);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}

void BrushTool::DrawLine(const Coords &from, const Coords &to) const noexcept{
    float step = sqrt(GetViewportWidth() * GetViewportWidth() + GetViewportHeight() * GetViewportHeight()) / (distance_pixels(from, to)) * scale * LinePointsPeriod;
    for(float progress = 0.0; progress < 1.0; progress += step){
        Coords curr(GetViewportWidth(), GetViewportHeight());
        lerp(curr, from, to, progress);
        DrawCircle(curr);
    }
    DrawCircle(to);
}

void BrushTool::OnDraw() const noexcept{
    DrawCircle(prevMousePos);
}

bool BrushTool::OnMouseMove(int x, int y) noexcept{
    if(isMouseDown){
        BindFramebuffer(GetState().GetGLID());
        Coords curr(GetViewportWidth(), GetViewportHeight());
        curr.SetXWindows(x);
        curr.SetYWindows(y);
        DrawLine(prevMousePos, curr);
        UnbindFramebuffer();
    }
    prevMousePos.SetXWindows(x);
    prevMousePos.SetYWindows(y);
    return true;
}

bool BrushTool::OnLMouseDown(int x, int y) noexcept{
    isMouseDown = true;
    prevMousePos.SetXWindows(x);
    prevMousePos.SetYWindows(y);
    BindFramebuffer(GetState().GetGLID());
    DrawCircle(prevMousePos);
    UnbindFramebuffer();
    return true;
}

bool BrushTool::OnLMouseUp(int x, int y) noexcept{
    if(isMouseDown){
        isMouseDown = false;
    }
    prevMousePos.SetXWindows(x);
    prevMousePos.SetYWindows(y);
    return true;
}

bool BrushTool::OnKeyDown(int vkCode, int repeat) noexcept{
    switch (vkCode)
    {
    case VK_OEM_6:{
        IncScale(false);
    } return true;
    case VK_OEM_4:{
        IncScale(true);
    } return true;
    case VK_OEM_1:{
        IncPower(false); 
    } return true;
    case VK_OEM_7:{
        IncPower(true);
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
    IncScale(false);
    return true;
}

bool BrushTool::OnScrollDown() noexcept{
    IncScale(true);
    return true;
}

BrushTool::BrushTool(int cx, int cy, const Texture &bg, const Texture &state, ColorPaletTool &colorPalet) noexcept: 
    DrawingTool(cx, cy, bg, state),
    colorPalet(colorPalet), prevMousePos(cx, cy){

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

float BrushTool::GetPower() const noexcept{
    return power;
}

float BrushTool::GetScale() const noexcept{
    return scale;
}

const ColorPaletTool &BrushTool::GetPalet() const noexcept{
    return colorPalet;
}

void BrushTool::IncScale(bool reverse) noexcept{
    if(reverse){
        scale *= 1.0 - scaleIncrement;
        if(scale < scaleMin) scale = scaleMin;  
    }
    else{
        scale *= 1.0 + scaleIncrement;
        if(scale > scaleMax) scale = scaleMax;
    }
}

void BrushTool::IncPower(bool reverse) noexcept{
    if(reverse){
        power = pow(power, 1.0 - powerIncrement);
        if(power < powerMin) power = powerMin; 
    }
    else{
        power = pow(power, 1.0 + powerIncrement);
        if(power < powerMin) power = powerMin; 
    }
}

BrushTool::~BrushTool() noexcept{
    glDeleteBuffers(1, &VBO);
}
