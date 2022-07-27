#include "MouseHighlightTool.hpp"
#include "MouseHighlight.hpp"
#include <math.h>

MouseHighlightTool::MouseHighlightTool(int cx, int cy, CommitHandler &commitHandler, const Texture &bg) noexcept
    :DrawingTool(cx, cy, commitHandler, bg){

}

void MouseHighlightTool::OnDraw() const noexcept{
    if(isMouseDown){
        float r = sqrt(pow(mX - mdX, 2) + pow(mY - mdY, 2)) / GetViewportWidth();
        MouseHighlight::GetRenderer().Draw((mdX + mX) / (float)GetViewportWidth() - 1.0, 1.0 - (mdY + mY) / (float)GetViewportHeight(), 0, 0, 0, 1.0-radius/2, 1.0/radius, r);
    }
    else{
        MouseHighlight::GetRenderer().Draw(mX * 2.0 / GetViewportWidth() - 1.0 ,1.0 - mY * 2.0 / GetViewportHeight(), 0, 0, 0,1.0 - radius  / 2, 1.0 / radius, radius);
    }
}

bool MouseHighlightTool::OnMouseMove(int x, int y) noexcept {
    mX = x;
    mY = y;
    return true;
}

bool MouseHighlightTool::OnLMouseDown(int x, int y) noexcept{
    isMouseDown = true;
    mX = x;
    mY = y;
    mdX = x;
    mdY = y;
    return true;
}

bool MouseHighlightTool::OnLMouseUp(int x, int y) noexcept{
    isMouseDown = false;
    mX = x;
    mY = y;
    return true;
}

bool MouseHighlightTool::OnKeyDown(int vkCode, int repeat) noexcept{return false;}
bool MouseHighlightTool::OnKeyUp(int vkCode) noexcept{return false;}
bool MouseHighlightTool::OnTextInput(std::wstring str) noexcept{return false;}

bool MouseHighlightTool::OnScrollUp() noexcept{
    radius -= 0.02;
    
    if(radius < 0.05) radius = 0.05;
    if(radius > 1) radius = 1;
    return true;
}
bool MouseHighlightTool::OnScrollDown() noexcept{
    radius += 0.02;
    
    if(radius < 0.05) radius = 0.05;
    if(radius > 1) radius = 1;
    return true;
}

