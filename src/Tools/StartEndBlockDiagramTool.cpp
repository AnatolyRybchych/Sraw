#include "StartEndBlockDiagramTool.hpp"
#include "../ResourceProvider.hpp"

void StartEndBlockDiagramTool::DrawBg() const noexcept{
    bgDrawingProgram.Draw(
        GetCurrMPosX(), 
        GetCurrMPosY(), 
        GetTextWidth(),
        GetSettings().GetFontSize(),
        GetSettings().GetPalet().GetRed(),
        GetSettings().GetPalet().GetGreen(),
        GetSettings().GetPalet().GetBlue()
    );
}

void StartEndBlockDiagramTool::DrawTxt() const noexcept{
    RenderText::GetDefaultRenderer()->Render(
        GetText().c_str(), 
        0, 
        GetSettings().GetFontSize(), 
        GetCurrMPosX() - GetTextWidth() / 2, GetCurrMPosY() - GetSettings().GetFontSize() / 2, 
        GetSettings().GetPalet().GetRed(),
        GetSettings().GetPalet().GetGreen(),
        GetSettings().GetPalet().GetBlue());
}

StartEndBlockDiagramTool::StartEndBlockDiagramTool(int cx, int cy, const Texture &bg, const Texture &state, BlockDiagramSetting &settings):
BlockDiagramTool(cx, cy, bg, state, settings), bgDrawingProgram(ResourceProvider::GetProvider().GetDrawStartEndDiagramBgProgram()){

}

int StartEndBlockDiagramTool::GetTextWidth() const noexcept{
    return RenderText::GetDefaultRenderer()->GetTextWidth(GetText().c_str(), 0, GetSettings().GetFontSize());;
}
