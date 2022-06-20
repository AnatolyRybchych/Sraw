#include "MouseHighlightTool.hpp"
#include "MouseHighlight.hpp"

MouseHighlightTool::MouseHighlightTool(int cx, int cy) noexcept
    :DrawingTool(cx, cy){

}

void MouseHighlightTool::OnDraw() const noexcept{
    MouseHighlight::GetRenderer().Draw(mX * 2.0 / GetViewportWidth() - 1.0 ,1.0 - mY * 2.0 / GetViewportHeight(), 0, 0, 0, 0.6, 0.9, 0.3);
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

void MouseHighlightTool::OnKeyDown(int vkCode, int repeat) noexcept{}

void MouseHighlightTool::OnKeyUp(int vkCode) noexcept{}

void MouseHighlightTool::OnTextInput(std::wstring str) noexcept{}

