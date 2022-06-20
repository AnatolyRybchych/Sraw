#include "DrawingTool.hpp"

DrawingTool::DrawingTool(int cx, int cy) noexcept{
    vpCx = cx;
    vpCy = cy;
}

void DrawingTool::SetOnCommitHandler(std::function<void()> handler) noexcept{
    onCommit = handler;
}

void DrawingTool::SetCommitDestinationTexture(GLuint texture) const noexcept{
    commitDst.AttachTexture2D(texture);
}

int DrawingTool::GetViewportWidth() const noexcept{
    return vpCx;
}

int DrawingTool::GetViewportHeight() const noexcept{
    return vpCy;
}

void DrawingTool::Commit() const noexcept{
    commitDst.Bind();
    Draw();
    commitDst.Unbind();
}

void DrawingTool::Draw() const noexcept{
    glViewport(0, 0, vpCx, vpCy);
    OnDraw();
}

void DrawingTool::Resize(int cx, int cy) noexcept{
    vpCx = cx;
    vpCy = cy;
    OnResize(cx, cy);
}

void DrawingTool::MouseMove(int x, int y) noexcept{
    OnMouseMove(x, y);
}

void DrawingTool::LMouseDown(int x, int y) noexcept{
    OnLMouseDown(x, y);
}

void DrawingTool::LMouseUp(int x, int y) noexcept{
    OnLMouseUp(x, y);
}

void DrawingTool::KeyDown(int vkCode, int repeat) noexcept{
    OnKeyDown(vkCode, repeat);
}

void DrawingTool::KeyUp(int vkCode) noexcept{
    OnKeyUp(vkCode);
}

void DrawingTool::TextInput(std::wstring str) noexcept{
    OnTextInput(str);
}

void DrawingTool::ScrollUp() noexcept{
    OnScrollUp();
}

void DrawingTool::ScrollDown() noexcept{
    OnScrollDown();
}
