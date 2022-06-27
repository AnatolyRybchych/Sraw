#pragma once
#include <functional>
#include <string>
#include "GlWrappers/Framebuffer.hpp"

class CommitHandler{
public:
    virtual void HandleCommit(std::function<void()> drawCommit) noexcept = 0;
};

class DrawingTool{
private:
    CommitHandler &commitHandler;
    int vpCx, vpCy;
protected://handlers should return true if requires to redraw
    virtual void OnDraw() const noexcept = 0;
    virtual void OnDrawCommit() noexcept = 0;
    virtual void OnResize(int cx, int cy) noexcept = 0;
    virtual bool OnMouseMove(int x, int y) noexcept = 0; 
    virtual bool OnLMouseDown(int x, int y) noexcept = 0;
    virtual bool OnLMouseUp(int x, int y) noexcept = 0;
    virtual bool OnKeyDown(int vkCode, int repeat) noexcept = 0;
    virtual bool OnKeyUp(int vkCode) noexcept = 0;
    virtual bool OnTextInput(std::wstring str) noexcept = 0;
    virtual bool OnScrollUp() noexcept = 0;
    virtual bool OnScrollDown() noexcept = 0;
public:
    
    DrawingTool(int cx, int cy, CommitHandler &commitHandler) noexcept;
    void SetOnCommitHandler(std::function<void()> handler) noexcept;
    void SetCommitDestinationTexture(GLuint texture) const noexcept;

    int GetViewportWidth() const noexcept;
    int GetViewportHeight() const noexcept;

    virtual void Commit() noexcept;

    void Draw() const noexcept;
    void Resize(int cx, int cy) noexcept;
    bool MouseMove(int x, int y) noexcept; 
    bool LMouseDown(int x, int y) noexcept;
    bool LMouseUp(int x, int y) noexcept;
    bool KeyDown(int vkCode, int repeat) noexcept;
    bool KeyUp(int vkCode) noexcept;
    bool TextInput(std::wstring str) noexcept;
    bool ScrollUp() noexcept;
    bool ScrollDown() noexcept;

    virtual ~DrawingTool() noexcept = default;
};
