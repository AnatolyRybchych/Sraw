#pragma once
#include "../DrawingTool.hpp"
#include "../GlWrappers/Texture.hpp"
#include "../GlWrappers/Framebuffer.hpp"
#include <memory>

class EraserTool: public DrawingTool{
private:
    static constexpr float scaleIncrement = 0.1; 
    static constexpr float scaleMin = 0.02; 
    static constexpr float scaleMax = 1.0; 
    
    GLuint prog;
    GLuint VBO;

    GLint vertex_pPos;
    GLint posPos;
    GLint viewportPos;
    GLint scalePos;
    GLint bgPos;

    bool isMouseDown = false;

    float scale = 0.1;

    int prevX;
    int prevY;

    void Erse(int x, int y) const noexcept;
    void ErseLine(int x1, int y1, int x2, int y2) const noexcept;
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
    EraserTool(int cx, int cy, CommitHandler &commitHandler, const Texture &bg) noexcept;

    ~EraserTool() noexcept;
};