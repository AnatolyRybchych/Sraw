#include "ColorPaletTool.hpp"

void ColorPaletTool::OnDraw() const noexcept{
}

void ColorPaletTool::OnDrawCommit() noexcept{
}

void ColorPaletTool::OnResize(int cx, int cy) noexcept{
}

bool ColorPaletTool::OnMouseMove(int x, int y) noexcept{
    return false;
} 

bool ColorPaletTool::OnLMouseDown(int x, int y) noexcept{
    return false;
}

bool ColorPaletTool::OnLMouseUp(int x, int y) noexcept{
    return false;
}

bool ColorPaletTool::OnKeyDown(int vkCode, int repeat) noexcept{
    return false;
}

bool ColorPaletTool::OnKeyUp(int vkCode) noexcept{
    return false;
}

bool ColorPaletTool::OnTextInput(std::wstring str) noexcept{
    return false;
}

bool ColorPaletTool::OnScrollUp() noexcept{
    return false;
}

bool ColorPaletTool::OnScrollDown() noexcept{
    return false;
}


ColorPaletTool::ColorPaletTool(int cx, int cy, CommitHandler &commitHandler) noexcept
    :DrawingTool(cx, cy, commitHandler){
    
    r = 0.8;
    g = 0.4;
    b = 0.2;
}

float ColorPaletTool::GetRed() const noexcept{
    return r;
}

float ColorPaletTool::GetGreen() const noexcept{
    return g;
}

float ColorPaletTool::GetBlue() const noexcept{
    return b;
}

void ColorPaletTool::SetRed(float value) noexcept{
    r = value;
}

void ColorPaletTool::SetGreen(float value) noexcept{
    g = value;
}

void ColorPaletTool::SetBlue(float value) noexcept{
    b = value;
}


