#include "DrawingCanvas.hpp"
#include "ShaderProgram.hpp"
#include "MouseHighlightTool.hpp"


#include <iostream>

const Texture &DrawingCanvas::GetBackground() const noexcept{
    return bg;
}

DrawingCanvas::DrawingCanvas(Texture &bg)
    :bg(bg) {
    drawingTool = std::unique_ptr<DrawingTool>(new MouseHighlightTool(100, 100));
}

void DrawingCanvas::Draw(){
    glViewport(0, 0, cx, cy);
    DrawImage::GetRenderer().Draw(currState->GetGLID());

    if(drawingTool){
        drawingTool->Draw();
    }
}

void DrawingCanvas::OnMouseMove(int x, int y){
    if(drawingTool){
        drawingTool->MouseMove(x, y);
    }
}

void DrawingCanvas::OnLMouseDown(int x, int y){
    if(drawingTool){
        drawingTool->LMouseDown(x, y);
    }
}

void DrawingCanvas::OnLMouseUp(int x, int y){
    if(drawingTool){
        drawingTool->LMouseDown(x, y);
    }
}


void DrawingCanvas::OnShow(int cx, int cy){
    this->cx = cx;
    this->cy = cy;

    if(drawingTool){
        drawingTool->Resize(cx, cy);
    }

    if(currState == nullptr){
        currState = std::unique_ptr<Texture>(new Texture(cx, cy));

        frameBuffer.Bind();
        glViewport(0, 0, cx, cy);
        frameBuffer.AttachTexture2D(currState->GetGLID());
        DrawImage::GetRenderer().Draw(bg.GetGLID());
        frameBuffer.Unbind();  
    }
}

void DrawingCanvas::OnkeyDown(int vkCode, int repeat){
    if(drawingTool){
        drawingTool->KeyDown(vkCode, repeat);
    }
}

void DrawingCanvas::Onkeyup(int vkCode){
    if(drawingTool){
        drawingTool->KeyUp(vkCode);
    }
}

void DrawingCanvas::OnScrollUp() noexcept{
    if(drawingTool){
        drawingTool->ScrollUp();
    }
}

void DrawingCanvas::OnScrollDown() noexcept{
    if(drawingTool){
        drawingTool->ScrollDown();
    }
}

void DrawingCanvas::OnTextInput(std::wstring str){
    if(drawingTool){
        drawingTool->TextInput(str);
    }
}