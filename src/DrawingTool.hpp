#pragma once
#include <functional>
#include <string>
#include "Framebuffer.hpp"

class DrawingTool{
private:
    std::function<void()> onCommit;
    Framebuffer commitDst;
    int vpCx, vpCy;
protected:
    virtual void OnDraw() const noexcept = 0;
    virtual void OnResize(int cx, int cy) noexcept = 0;
    virtual void OnMouseMove(int x, int y) noexcept = 0; 
    virtual void OnLMouseDown(int x, int y) noexcept = 0;
    virtual void OnLMouseUp(int x, int y) noexcept = 0;
    virtual void OnKeyDown(int vkCode, int repeat) noexcept = 0;
    virtual void OnKeyUp(int vkCode) noexcept = 0;
    virtual void OnTextInput(std::wstring str) noexcept = 0;
    virtual void OnScrollUp() noexcept = 0;
    virtual void OnScrollDown() noexcept = 0;
public:
    DrawingTool(int cx, int cy) noexcept;
    void SetOnCommitHandler(std::function<void()> handler) noexcept;
    void SetCommitDestinationTexture(GLuint texture) const noexcept;

    int GetViewportWidth() const noexcept;
    int GetViewportHeight() const noexcept;

    virtual void Commit() const noexcept;

    void Draw() const noexcept;
    void Resize(int cx, int cy) noexcept;
    void MouseMove(int x, int y) noexcept; 
    void LMouseDown(int x, int y) noexcept;
    void LMouseUp(int x, int y) noexcept;
    void KeyDown(int vkCode, int repeat) noexcept;
    void KeyUp(int vkCode) noexcept;
    void TextInput(std::wstring str) noexcept;
    void ScrollUp() noexcept;
    void ScrollDown() noexcept;

    virtual ~DrawingTool() noexcept = default;
};
