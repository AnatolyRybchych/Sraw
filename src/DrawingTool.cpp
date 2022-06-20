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

bool DrawingTool::MouseMove(int x, int y) noexcept{
    return OnMouseMove(x, y);
}

bool DrawingTool::LMouseDown(int x, int y) noexcept{
    return OnLMouseDown(x, y);
}

bool DrawingTool::LMouseUp(int x, int y) noexcept{
    return OnLMouseUp(x, y);
}

bool DrawingTool::KeyDown(int vkCode, int repeat) noexcept{
    return OnKeyDown(vkCode, repeat);
}

bool DrawingTool::KeyUp(int vkCode) noexcept{
    return OnKeyUp(vkCode);
}

bool DrawingTool::TextInput(std::wstring str) noexcept{
    return OnTextInput(str);
}

bool DrawingTool::ScrollUp() noexcept{
    return OnScrollUp();
}

bool DrawingTool::ScrollDown() noexcept{
    return OnScrollDown();
}
