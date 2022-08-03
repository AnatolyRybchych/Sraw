#include "PrimitiveTool.hpp"
#include "../Basics.hpp"

void PrimitiveTool::_DrawPrimitive() const noexcept{

    Coords _p1(GetViewportWidth(), GetViewportHeight());
    Coords _p2(GetViewportWidth(), GetViewportHeight());

    if(isCtrlDown){
        double cx = p1.GetXGlPixels() - p2.GetXGlPixels();
        double cy = p1.GetYGlPixels() - p2.GetYGlPixels();

        _p1.SetXGlPixels(p1.GetXGlPixels() + cx * 0.5);
        _p1.SetYGlPixels(p1.GetYGlPixels() + cy * 0.5);
        _p2.SetXGlPixels(p2.GetXGlPixels() + cx * 0.5);
        _p2.SetYGlPixels(p2.GetYGlPixels() + cy * 0.5);
    }
    else{
        _p1 = p1;
        _p2 = p2;
    }

    DrawPrimitive(_p1, _p2);
}

void PrimitiveTool::OnDraw() const noexcept{
    if(isMouseDown){
        _DrawPrimitive();
    }
    else{
        if(lastMousePos.GetXGl() < 0){
            Coords _p1(GetViewportWidth(), GetViewportHeight());
            Coords _p2(GetViewportWidth(), GetViewportHeight());

            _p1.SetXGl(1.0 - previewSize - previewOffset);
            _p1.SetYGl(1.0 - previewOffset);
            _p2.SetXGl(1.0 - previewOffset);
            _p2.SetYGl(1.0 - previewSize - previewOffset);

            DrawPrimitive(_p1, _p2);
        }
        else{
            Coords _p1(GetViewportWidth(), GetViewportHeight());
            Coords _p2(GetViewportWidth(), GetViewportHeight());

            _p1.SetXGl(-1.0 + previewSize + previewOffset);
            _p1.SetYGl(1.0 - previewOffset);
            _p2.SetXGl(-1.0 + previewOffset);
            _p2.SetYGl(1.0 - previewSize - previewOffset);

            DrawPrimitive(_p1, _p2);
        }
    }
}

bool PrimitiveTool::OnMouseMove(int x, int y) noexcept{
    bool ret = false;
    if(isMouseDown){
        p2.SetXWindows(x);
        p2.SetYWindows(y);

        ret = true;
    }
    else if(lastMousePos.GetXGl() / 0.0 != (x / (float)GetViewportWidth() - 0.5) / 0.0){
        ret = true;
    }

    lastMousePos.SetXWindows(x);
    lastMousePos.SetYWindows(y);
    return ret;
} 

bool PrimitiveTool::OnLMouseDown(int x, int y) noexcept{
    isMouseDown = true;
    lastMousePos.SetXWindows(x);
    lastMousePos.SetYWindows(y);

    p1.SetXWindows(x);
    p1.SetYWindows(y);
    p2.SetXWindows(x);
    p2.SetYWindows(y);

    return true;;
}

bool PrimitiveTool::OnLMouseUp(int x, int y) noexcept{
    isMouseDown = false;
    lastMousePos.SetXWindows(x);
    lastMousePos.SetYWindows(y);

    BindFramebuffer(GetState().GetGLID());
    _DrawPrimitive();
    UnbindFramebuffer();

    return true;
}

bool PrimitiveTool::OnKeyDown(int vkCode, int repeat) noexcept{
    switch (vkCode){
    case VK_OEM_6:{
        brush.IncScale(false);
    } return true;
    case VK_OEM_4:{
        brush.IncScale(true);
    } return true;
    case VK_OEM_1:{
        brush.IncPower(false); 
    } return true;
    case VK_OEM_7:{
        brush.IncPower(true);
    } return true;
    case VK_RCONTROL:
    case VK_LCONTROL:
    case VK_CONTROL:{
        isCtrlDown = true;
    } return true;
    default: return false;
    }
}

bool PrimitiveTool::OnKeyUp(int vkCode) noexcept{
    switch (vkCode){
    case VK_RCONTROL:
    case VK_LCONTROL:
    case VK_CONTROL:{
        isCtrlDown = false;
    } return true;
    default: return false;
    }
}

bool PrimitiveTool::OnTextInput(std::wstring str) noexcept{
    return false;
}

bool PrimitiveTool::OnScrollUp() noexcept{
    brush.IncScale(true);
    return true;
}

bool PrimitiveTool::OnScrollDown() noexcept{
    brush.IncScale(false);
    return true;
}

PrimitiveTool::PrimitiveTool(int cx, int cy, const Texture &bg, const Texture &state, BrushTool &brush) noexcept
:DrawingTool(cx, cy, bg, state), brush(brush), lastMousePos(cx, cy), p1(cx, cy), p2(cx, cy){

}

const BrushTool &PrimitiveTool::GetBrush() const noexcept{
    return brush;
}