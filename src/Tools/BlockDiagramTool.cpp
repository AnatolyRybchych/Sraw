#include "BlockDiagramTool.hpp"

BlockDiagramSetting::BlockDiagramSetting(ColorPaletTool &paletTool,int fontSize) noexcept
:paletTool(paletTool), fontSize(fontSize){
    if(fontSize > 1000) fontSize = 1000;
    else if(fontSize < 18) fontSize = 18;
}

const ColorPaletTool &BlockDiagramSetting::GetPalet() const noexcept{
    return paletTool;
}

ColorPaletTool &BlockDiagramSetting::GetPaletRef() noexcept{
    return paletTool;
}

void BlockDiagramSetting::FontSizeInc() noexcept{
    fontSize *= 1.0 + 0.1;
    if(fontSize > 1000) fontSize = 1000;
}

void BlockDiagramSetting::FontSizeDec() noexcept{
    fontSize *= 1.0 - 0.1;
    if(fontSize < 18) fontSize = 18;
}

int BlockDiagramSetting::GetFontSize() const noexcept{
    return fontSize;
}


BlockDiagramTool::BlockDiagramTool(int cx, int cy, CommitHandler &commitHandler, const Texture &bg, BlockDiagramSetting &settings)
:DrawingTool(cx, cy, commitHandler, bg), settings(settings){
}

int BlockDiagramTool::GetCurrMPosX() const noexcept{
    return currX;
}

int BlockDiagramTool::GetCurrMPosY() const noexcept{
    return currY;
}

const BlockDiagramSetting &BlockDiagramTool::GetSettings() const noexcept{
    return settings;
}

BlockDiagramSetting &BlockDiagramTool::GetSettingsRef() noexcept{
    return settings;
}

void BlockDiagramTool::OnDraw() const noexcept{
    DrawBg();
    DrawTxt();
}

bool BlockDiagramTool::OnMouseMove(int x, int y) noexcept{
    currX = x;
    currY = y;
    return true;
}   

bool BlockDiagramTool::OnLMouseDown(int x, int y) noexcept{
    currX = x;
    currY = y;
    isMouseDown = true;
    return false;
}

bool BlockDiagramTool::OnLMouseUp(int x, int y) noexcept{
    currX = x;
    currY = y;

    if(isMouseDown){
        BindFramebuffer(GetCommitBuffer().GetGLID());
        OnDraw();
        UnbindFramebuffer();
        Commit();
        ClearCommitBuffer();
    }

    isMouseDown = false;

    return true;
}

bool BlockDiagramTool::OnKeyDown(int vkCode, int repeat) noexcept{
    switch (vkCode){
    case VK_CONTROL:
    case VK_LCONTROL:
    case VK_RCONTROL:{
        isControlDown = true;
    } return false;
    case VK_BACK:{
        if(isControlDown){
            text.clear();
            return true;
        } 
        if(text.size() != 0){
            text.erase(text.begin() + (text.size() - 1));
            return false;
        } 
    }return true;
    default: return false;
    }
}

bool BlockDiagramTool::OnKeyUp(int vkCode) noexcept{
    switch (vkCode){
    case VK_CONTROL:
    case VK_LCONTROL:
    case VK_RCONTROL:{
        isControlDown = false;
    } return false;
    default: return false;
    }
}

bool BlockDiagramTool::OnTextInput(std::wstring str) noexcept{
    for(auto ch:str){
        if(((ch  > 0x20) 
        && (ch < 127 || ch > 159)) 
        || ch == L' '){
            text += std::wstring(1, ch);
        }
    }
    return true;
}

bool BlockDiagramTool::OnScrollUp() noexcept{
    settings.FontSizeInc();
    return true;
}

bool BlockDiagramTool::OnScrollDown() noexcept{
    settings.FontSizeDec();
    return true;
}

std::wstring BlockDiagramTool::GetText() const noexcept{
    if(text == L""){
        return L"Text";
    }
    else{
        return text;
    }
}

void BlockDiagramTool::SetText(std::wstring text) noexcept{
    this->text = text;
}
