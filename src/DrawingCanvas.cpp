#include "DrawingCanvas.hpp"
#include "GlWrappers/ShaderProgram.hpp"
#include "Tools/MouseHighlightTool.hpp"
#include "Tools/SelectToolTool.hpp"

#include <iostream>

const Texture &DrawingCanvas::GetBackground() const noexcept{
    return bg;
}

const Texture &DrawingCanvas::GetCurrentState() const noexcept{
    return currState;
}

DrawingCanvas::DrawingCanvas(Texture &bg, Quitable &quitable, const DrawingTarget &DrawingTarget, int cx, int cy)
    :bg(bg),
    currState(cx, cy),
    toolMenuManager(cx, cy, bg, quitable, DrawingTarget, currState){

    frameBuffer.Bind();
    glViewport(0, 0, cx, cy);
    frameBuffer.AttachTexture2D(currState.GetGLID());
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    frameBuffer.Unbind(); 
    this->cx = cx;
    this->cy = cy;
}

void DrawingCanvas::Draw(){
    glViewport(0, 0, cx, cy);
    DrawImage::GetRenderer().Draw(bg.GetGLID());
    DrawImage::GetRenderer().Draw(currState.GetGLID());
    
    toolMenuManager.GetCurrTool().Draw();
}

bool DrawingCanvas::OnMouseMove(int x, int y){
    return toolMenuManager.GetCurrTool().MouseMove(x, y);
}

bool DrawingCanvas::OnLMouseDown(int x, int y){
    return toolMenuManager.GetCurrTool().LMouseDown(x, y);
}

bool DrawingCanvas::OnLMouseUp(int x, int y){
    return toolMenuManager.GetCurrTool().LMouseUp(x, y);
}

bool DrawingCanvas::OnRMouseDown(int x, int y){
    toolMenuManager.OpenToolMenu();
    return true;
}

bool DrawingCanvas::OnRMouseUp(int x, int y){
    return true;
}

bool DrawingCanvas::OnkeyDown(int vkCode, int repeat){
    return toolMenuManager.GetCurrTool().KeyDown(vkCode, repeat);
}

bool DrawingCanvas::Onkeyup(int vkCode){
    return toolMenuManager.GetCurrTool().KeyUp(vkCode);
}

bool DrawingCanvas::OnScrollUp() noexcept{
    return toolMenuManager.GetCurrTool().ScrollUp();
}

bool DrawingCanvas::OnScrollDown() noexcept{
    return toolMenuManager.GetCurrTool().ScrollDown();
}

bool DrawingCanvas::OnTextInput(std::wstring str){
    return toolMenuManager.GetCurrTool().TextInput(str);
}