#include "MouseHighlightTool.hpp"
#include "MouseHighlight.hpp"
#include <iostream>
#include <math.h>

MouseHighlightTool::MouseHighlightTool(int cx, int cy) noexcept
    :DrawingTool(cx, cy){

}

void MouseHighlightTool::OnDraw() const noexcept{
    MouseHighlight::GetRenderer().Draw(mX * 2.0 / GetViewportWidth() - 1.0 ,1.0 - mY * 2.0 / GetViewportHeight(), 0, 0, 0, 0.5, 1.0 / radius, radius);
}

void MouseHighlightTool::OnResize(int cx, int cy) noexcept{}

void MouseHighlightTool::OnMouseMove(int x, int y) noexcept {
    mX = x;
    mY = y;
}

void MouseHighlightTool::OnLMouseDown(int x, int y) noexcept{
    mX = x;
    mY = y;
}

void MouseHighlightTool::OnLMouseUp(int x, int y) noexcept{
    mX = x;
    mY = y;
}

void MouseHighlightTool::OnKeyDown(int vkCode, int repeat) noexcept{
    std::cout<<vkCode<<"\n";
}

void MouseHighlightTool::OnKeyUp(int vkCode) noexcept{}
void MouseHighlightTool::OnTextInput(std::wstring str) noexcept{}

void MouseHighlightTool::OnScrollUp() noexcept{
    radius -= 0.02;
    
    if(radius < 0.05) radius = 0.05;
    if(radius > 1) radius = 1;
}
void MouseHighlightTool::OnScrollDown() noexcept{
    radius += 0.02;
    
    if(radius < 0.05) radius = 0.05;
    if(radius > 1) radius = 1;
}

