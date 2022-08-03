#include "RectTool.hpp"
#include "../RectRenderer.hpp"

void RectTool::DrawPrimitive(const Coords &mouseDownCoord, const Coords &mouseUpCoord) const noexcept{
    RectOutlineTool::DrawPrimitive(mouseDownCoord, mouseUpCoord);
    RectRenderer::GetRenderer().Fill(
        mouseDownCoord, 
        mouseUpCoord, 
        GetBrush().GetPalet().GetRed(),
        GetBrush().GetPalet().GetGreen(),
        GetBrush().GetPalet().GetBlue(),
        1
    );
};

RectTool::RectTool(int cx, int cy, const Texture &bg, const Texture &state, BrushTool &brush) noexcept
:RectOutlineTool(cx, cy, bg, state, brush){

};
