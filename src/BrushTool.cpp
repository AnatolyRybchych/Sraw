#include "BrushTool.hpp"


void BrushTool::OnDraw() const noexcept{
}

void BrushTool::BrushTool::OnResize(int cx, int cy) noexcept{
}

bool BrushTool::OnMouseMove(int x, int y) noexcept{
    return false;
}

bool BrushTool::OnLMouseDown(int x, int y) noexcept{
    return false;
}

bool BrushTool::OnLMouseUp(int x, int y) noexcept{
    return false;
}

bool BrushTool::OnKeyDown(int vkCode, int repeat) noexcept{
    return false;
}

bool BrushTool::OnKeyUp(int vkCode) noexcept{
    return false;
}

bool BrushTool::OnTextInput(std::wstring str) noexcept{
    return false;
}

bool BrushTool::OnScrollUp() noexcept{
    return false;
}

bool BrushTool::OnScrollDown() noexcept{
    return false;
}

BrushTool::BrushTool(int cx, int cy) noexcept: DrawingTool(cx, cy){

}