#pragma once
#include "../DrawingTool.hpp"
#include "../GlWrappers/Framebuffer.hpp"
#include <GL/glew.h>
#include "../Coords.hpp"

class SelectionTool: public DrawingTool{
private:
    Coords p1;
    Coords p2;
    Coords lastMousePos;

    const Texture &state;
    GLuint erseBuffer;

    GLuint selection;
    bool isControlDown = false;

    int stage;

    int GetSelectionX() const noexcept;
    int GetSelectionY() const noexcept;
    int GetSelectionCx() const noexcept;
    int GetSelectionCy() const noexcept;
    bool IsPointInSelectionRect(int x, int y) const noexcept;
    void CopyStateToSelection(int x, int y, int cx, int cy) noexcept;
    void ErseRgn(int x, int y, int cx, int cy) noexcept;
    void PasteSelection(int x, int y, int cx, int cy) noexcept;
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
    SelectionTool(int cx, int cy, CommitHandler &commitHandler, const Texture &bg, const Texture &state);
    ~SelectionTool();
};