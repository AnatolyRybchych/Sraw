#include "DrawingTool.hpp"
#include "DrawImage.hpp"

DrawingTool::DrawingTool(int cx, int cy, CommitHandler &commitHandler, const Texture &bg) noexcept
    :commitHandler(commitHandler),
    bg(bg),
    buffer(cx, cy),
    framebuffer(){
    vpCx = cx;
    vpCy = cy;

    ClearCommitBuffer();
}

const Texture &DrawingTool::GetCommitBuffer() const noexcept{
    return buffer;
}

const Texture &DrawingTool::GetBg() const noexcept{
    return bg;
}

void DrawingTool::BindFramebuffer(GLuint texture) noexcept{
    framebuffer.Bind();
    framebuffer.AttachTexture2D(texture);
}

void DrawingTool::UnbindFramebuffer() noexcept{
    framebuffer.Unbind();
}

void DrawingTool::ClearCommitBuffer() noexcept{
    BindFramebuffer(buffer.GetGLID());
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    UnbindFramebuffer();
}

void DrawingTool::OnDrawCommit() noexcept{
    DrawImage::GetRenderer().Draw(buffer.GetGLID());
}

int DrawingTool::GetViewportWidth() const noexcept{
    return vpCx;
}

int DrawingTool::GetViewportHeight() const noexcept{
    return vpCy;
}

void DrawingTool::Commit() noexcept{
    commitHandler.HandleCommit(std::bind(OnDrawCommit, this));
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
