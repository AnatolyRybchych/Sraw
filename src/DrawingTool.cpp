#include "DrawingTool.hpp"
#include "DrawImage.hpp"

DrawingTool::DrawingTool(int cx, int cy, const Texture &bg, const Texture &state) noexcept
    :state(state),
    bg(bg),
    framebuffer(){
    vpCx = cx;
    vpCy = cy;
}

const Texture &DrawingTool::GetState() const noexcept{
    return state;
}

const Texture &DrawingTool::GetBg() const noexcept{
    return bg;
}

void DrawingTool::BindFramebuffer(GLuint texture) const noexcept{
    framebuffer.Bind();
    framebuffer.AttachTexture2D(texture);
}

void DrawingTool::UnbindFramebuffer() const noexcept{
    framebuffer.Unbind();
}

int DrawingTool::GetViewportWidth() const noexcept{
    return vpCx;
}

int DrawingTool::GetViewportHeight() const noexcept{
    return vpCy;
}

void DrawingTool::Draw() const noexcept{
    glViewport(0, 0, vpCx, vpCy);
    OnDraw();
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
