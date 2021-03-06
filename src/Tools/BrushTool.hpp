#pragma once
#include <memory>
#include "../DrawingTool.hpp"
#include "ColorPaletTool.hpp"
#include "../GlWrappers/Texture.hpp"
#include "../GlWrappers/Framebuffer.hpp"
#include "../Coords.hpp"


class BrushTool:public DrawingTool{
private:
    static constexpr float scaleIncrement = 0.1; 
    static constexpr float scaleMin = 0.004; 
    static constexpr float scaleMax = 1.0; 
    static constexpr float powerIncrement = 0.1; 
    static constexpr float powerMin = 0.001; 
    static constexpr float powerMax = 0.5; 

    GLuint prog;
    GLuint VBO;

    GLint vertex_pPos;
    GLint colorPos;
    GLint posPos;
    GLint viewportPos;
    GLint powerPos;
    GLint scalePos;

    bool isMouseDown = false;

    float power = 0.5;
    float scale = 0.02;

    Coords prevMousePos;

    ColorPaletTool &colorPalet;
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
    static constexpr float LinePointsPeriod = 0.2; 

    BrushTool(int cx, int cy, const Texture &bg, const Texture &state, ColorPaletTool &colorPalet) noexcept;
    float GetPower() const noexcept;
    float GetScale() const noexcept;
    void IncScale(bool reverse) noexcept;
    void IncPower(bool reverse) noexcept;
    const ColorPaletTool &GetPalet() const noexcept;

    void DrawCircle(const Coords &pos) const noexcept;
    void DrawLine(const Coords &from, const Coords &to) const noexcept;
    
    ~BrushTool() noexcept;
};
