#pragma once
#include "../DrawingTool.hpp"
#include "../GlWrappers/Framebuffer.hpp"
#include <GL/glew.h>
#include "../Coords.hpp"

//uses opengl pixel coords
class Selection{
private:
    Framebuffer fb;
    GLuint texture;

    int srcX, srcY, srcCx, srcCy;

    bool hasContent = false;
public:
    Selection() noexcept;
    ~Selection() noexcept;
    void CopyContentFromTexture(GLuint texture, int x, int y, int cx, int cy) noexcept;
    void UnsetContent() noexcept;
    void DrawStretch(int x, int y, int cx, int cy) const noexcept;
    bool HasContent() const noexcept;

    int GetSrcX() const noexcept;
    int GetSrcY() const noexcept;
    int GetSrcCx() const noexcept;
    int GetSrcCy() const noexcept;
};

class SelectionTool: public DrawingTool{
private:
    Selection selection;

    Coords p1;
    Coords p2;

    bool isMouseDown = false;
    bool isControlDown = false;
    bool isSelected = false;
protected://handlers should return true if requires to redraw
    virtual void OnDraw() const noexcept override;
    virtual bool OnMouseMove(int x, int y) noexcept override; 
    virtual bool OnLMouseDown(int x, int y) noexcept override;
    virtual bool OnLMouseUp(int x, int y) noexcept override;
    virtual bool OnKeyDown(int vkCode, int repeat) noexcept override;
    virtual bool OnKeyUp(int vkCode) noexcept override;
    virtual bool OnTextInput(std::wstring str) noexcept override;
    virtual bool OnScrollUp() noexcept override;
    virtual bool OnScrollDown() noexcept override;
public:
    SelectionTool(int cx, int cy, CommitHandler &commitHandler, const Texture &bg);
};