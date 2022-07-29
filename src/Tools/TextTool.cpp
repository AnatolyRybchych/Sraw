#include "TextTool.hpp"
#include "../GlWrappers/RenderText.hpp"

void TextTool::OnDraw() const noexcept{
    int textWidth = RenderText::GetDefaultRenderer()->GetTextWidth(GetText().c_str(), 0, fontSize);

    RenderText::GetDefaultRenderer()->Render(
        GetText().c_str(), 
        0, 
        fontSize, 
        currX - textWidth / 2, currY - fontSize / 2, 
        colorPalete.GetRed(),
        colorPalete.GetGreen(),
        colorPalete.GetBlue());
}

bool TextTool::OnMouseMove(int x, int y) noexcept{
    currX = x;
    currY = y;
    return true;
} 

bool TextTool::OnLMouseDown(int x, int y) noexcept{
    currX = x;
    currY = y;
    isMouseDown = true;
    return false;
}  

bool TextTool::OnLMouseUp(int x, int y) noexcept{
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

bool TextTool::OnKeyDown(int vkCode, int repeat) noexcept{
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

bool TextTool::OnKeyUp(int vkCode) noexcept{
    switch (vkCode){
    case VK_CONTROL:
    case VK_LCONTROL:
    case VK_RCONTROL:{
        isControlDown = false;
    } return false;
    default: return false;
    }
}

bool TextTool::OnTextInput(std::wstring str) noexcept{
    for(auto ch:str){
        if(((ch  > 0x20) 
        && (ch < 127 || ch > 159)) 
        || ch == L' '){
            text += std::wstring(1, ch);
        }
    }
    return true;
}

bool TextTool::OnScrollUp() noexcept{
    IncFontSize(false);
    return true;
}

bool TextTool::OnScrollDown() noexcept{
    IncFontSize(true);
    return true;
}


TextTool::TextTool(int cx, int cy, CommitHandler &commitHandler, const Texture &bg, ColorPaletTool &colorPalete) noexcept
:DrawingTool(cx, cy, commitHandler, bg), colorPalete(colorPalete){
    
}

void TextTool::IncFontSize(bool dec) noexcept{
    if(dec){
        fontSize *= 1.0 - FontIncrement;
    }
    else{
        fontSize *= 1.0 + FontIncrement;
    }

    if(fontSize > MaxFontSize) fontSize = MaxFontSize;
    else if(fontSize < MinFontSize) fontSize = MinFontSize;
}

std::wstring TextTool::GetText() const noexcept{
    if(text == L""){
        return L"Text";
    }
    else{
        return text;
    }
}