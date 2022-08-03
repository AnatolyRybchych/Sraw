#pragma once
#include "../DrawingTool.hpp"
#include "../GlWrappers/Texture.hpp"
#include "../GlWrappers/Framebuffer.hpp"
#include "../Coords.hpp"
#include <memory>

class EraserTool: public DrawingTool{
private:
    static constexpr float scaleIncrement = 0.1; 
    static constexpr float scaleMin = 0.02; 
    static constexpr float scaleMax = 1.0; 
    GLuint erseTex;

    bool isMouseDown = false;

    float scale = 0.1;

    Coords prevMousePos;

    void Erse(const Coords &pos) const noexcept;
    void ErseLine(const Coords &from, const Coords &to) const noexcept;
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
    EraserTool(int cx, int cy, const Texture &bg, const Texture &state) noexcept;

    ~EraserTool() noexcept;
};