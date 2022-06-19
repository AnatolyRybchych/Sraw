#include "DrawingCanvas.hpp"
#include "ShaderProgram.hpp"


#include <iostream>

const Texture &DrawingCanvas::GetBackground() const noexcept{
    return bg;
}

DrawingCanvas::DrawingCanvas(Texture &bg)
    :bg(bg) {
}

void DrawingCanvas::Draw(){
    glViewport(0, 0, cx, cy);
    DrawImage::GetRenderer().Draw(currState->GetGLID());

    MouseHighlight::GetRenderer().Draw(mX * 2.0 / cx - 1.0 ,1.0 - mY * 2.0 / cy, 0, 0, 0, 0.6, 0.9, 0.3);
}

bool DrawingCanvas::OnMouseMove(int x, int y){
    mX = x;
    mY = y;
    return true;
}

bool DrawingCanvas::OnLMouseDown(int x, int y){
    mX = x;
    mY = y;
    return false;
}

bool DrawingCanvas::OnLMouseUp(int x, int y){
    mX = x;
    mY = y;
    return false;
}


void DrawingCanvas::OnShow(int cx, int cy){
    this->cx = cx;
    this->cy = cy;

    if(currState == nullptr){
        currState = std::unique_ptr<Texture>(new Texture(cx, cy));

        frameBuffer.Bind();
        glViewport(0, 0, cx, cy);
        frameBuffer.AttachTexture2D(currState->GetGLID());
        DrawImage::GetRenderer().Draw(bg.GetGLID());
        frameBuffer.Unbind();  
    }
}