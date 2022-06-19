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
}

bool DrawingCanvas::OnMouseMove(int x, int y){
    return false;
}

bool DrawingCanvas::OnLMouseDown(int x, int y){
    return false;
}

bool DrawingCanvas::OnLMouseUp(int x, int y){
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