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

bool DrawingCanvas::OnMouseMove(int x, int y){
    if(drawingTool){
        return drawingTool->MouseMove(x, y);
    }
    return false;
}

bool DrawingCanvas::OnLMouseDown(int x, int y){
    if(drawingTool){
        return drawingTool->LMouseDown(x, y);
    }
    return false;
}

bool DrawingCanvas::OnLMouseUp(int x, int y){
    if(drawingTool){
        return drawingTool->LMouseUp(x, y);
    }
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

    if(drawingTool){
        drawingTool->Resize(cx, cy);
    }
}

bool DrawingCanvas::OnkeyDown(int vkCode, int repeat){
    if(drawingTool){
        return drawingTool->KeyDown(vkCode, repeat);
    }
    return false;
}

bool DrawingCanvas::Onkeyup(int vkCode){
    if(drawingTool){
        return drawingTool->KeyUp(vkCode);
    }
    return false;
}

bool DrawingCanvas::OnScrollUp() noexcept{
    if(drawingTool){
        return drawingTool->ScrollUp();
    }
    return false;
}

bool DrawingCanvas::OnScrollDown() noexcept{
    if(drawingTool){
        return drawingTool->ScrollDown();
    }
    return false;
}

bool DrawingCanvas::OnTextInput(std::wstring str){
    if(drawingTool){
        return drawingTool->TextInput(str);
    }
    return false;
}