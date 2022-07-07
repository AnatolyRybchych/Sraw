#pragma once
#include <memory>
#include "../DrawingTool.hpp"
#include "ColorPaletTool.hpp"
#include "../GlWrappers/Texture.hpp"
#include "../GlWrappers/Framebuffer.hpp"


class BrushTool:public DrawingTool{
private:
    static constexpr float scaleIncrement = 0.1; 
    static constexpr float scaleMin = 0.004; 
    static constexpr float scaleMax = 1.0; 
    static constexpr float powerMin = 0.001; 
    static constexpr float powerMax = 0.5; 
    std::unique_ptr<Texture> buffer;
    std::unique_ptr<Framebuffer> frameBuffer;

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
    float colorR = 1.0;
    float colorG = 0.0;
    float colorB = 0.0;

    int prevX;
    int prevY;

    void ClearBuffer() const noexcept;
    void DrawCircle(int x, int y) const noexcept;
    ColorPaletTool &colorPalet;
protected://handlers should return true if requires to redraw
    virtual void OnDraw() const noexcept override;
    virtual void OnDrawCommit() noexcept override;
    virtual void OnResize(int cx, int cy) noexcept override;
    virtual bool OnMouseMove(int x, int y) noexcept override; 
    virtual bool OnLMouseDown(int x, int y) noexcept override;
    virtual bool OnLMouseUp(int x, int y) noexcept override;
    virtual bool OnKeyDown(int vkCode, int repeat) noexcept override;
    virtual bool OnKeyUp(int vkCode) noexcept override;
    virtual bool OnTextInput(std::wstring str) noexcept override;
    virtual bool OnScrollUp() noexcept override;
    virtual bool OnScrollDown() noexcept override;
    
public:
    BrushTool(int cx, int cy, CommitHandler &commitHandler, ColorPaletTool &colorPalet) noexcept;
    ~BrushTool() noexcept;
};
