#include "CircleTool.hpp"


#include "../Basics.hpp"

void CircleTool::DrawPrimitive(const Coords &mouseDownCoord, const Coords &mouseUpCoord) const noexcept{
    double cx = mouseDownCoord.GetXGlPixels() - mouseUpCoord.GetXGlPixels();
    double cy = mouseDownCoord.GetYGlPixels() - mouseUpCoord.GetYGlPixels();

    float step = sqrt(GetViewportWidth() * GetViewportWidth() + GetViewportHeight() * GetViewportHeight()) / (distance_pixels(mouseDownCoord, mouseUpCoord)) * GetBrush().GetScale() * GetBrush().LinePointsPeriod * M_PI;

    Coords p = mouseDownCoord;

    for(double angle = 0.0; angle < M_PI * 2; angle += step){
        p.SetXGlPixels(mouseDownCoord.GetXGlPixels() + cx * (sin(angle) * 0.5 - 0.5));
        p.SetYGlPixels(mouseDownCoord.GetYGlPixels() + cy * (cos(angle) * 0.5 - 0.5));
        GetBrush().DrawCircle(p);
    }
};

CircleTool::CircleTool(int cx, int cy, const Texture &bg, const Texture &state, BrushTool &brush) noexcept
:PrimitiveTool(cx, cy, bg, state, brush){

};