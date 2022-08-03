#include "../ResourceProvider.hpp"
#include "EraserTool.hpp"
#include "../GlWrappers/ShaderProgram.hpp"
#include "../DrawImage.hpp"
#include "../Basics.hpp"

void EraserTool::Erse(const Coords &pos) const noexcept{
    glEnable(GL_SCISSOR_TEST);
    
    BindFramebuffer(GetState().GetGLID());
    glScissor(pos.GetXGlPixels() - GetViewportWidth() * scale * 0.5, pos.GetYGlPixels() - GetViewportWidth() * scale * 0.5, GetViewportWidth() * scale, GetViewportWidth() * scale);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    UnbindFramebuffer();
    
    glDisable(GL_SCISSOR_TEST);
}

void EraserTool::ErseLine(const Coords &from, const Coords &to) const noexcept{
    float step = sqrt(GetViewportWidth() * GetViewportWidth() + GetViewportHeight() * GetViewportHeight()) / (distance_pixels(from , to)) * scale * 0.2;
    for(float progress = 0.0; progress < 1.0; progress += step){
        Coords curr(GetViewportWidth(), GetViewportHeight());
        lerp(curr, from , to, progress);
        Erse(curr);
    }
}

void EraserTool::OnDraw() const noexcept{
    int erseWidthPixels = GetViewportWidth() * scale;
    
    char *data = new char[erseWidthPixels * erseWidthPixels * 4];

    BindFramebuffer(GetBg().GetGLID());
    glReadPixels(prevMousePos.GetXGlPixels() - erseWidthPixels / 2, prevMousePos.GetYGlPixels() - erseWidthPixels / 2, erseWidthPixels, erseWidthPixels, GL_RGBA, GL_UNSIGNED_BYTE, data);
    UnbindFramebuffer();

    glBindTexture(GL_TEXTURE_2D, erseTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, erseWidthPixels, erseWidthPixels, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);

    int vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    glViewport(prevMousePos.GetXGlPixels() - erseWidthPixels / 2, prevMousePos.GetYGlPixels() - erseWidthPixels / 2, erseWidthPixels, erseWidthPixels);
    DrawImage::GetRenderer().Draw(erseTex);
    glViewport(vp[0], vp[1], vp[2], vp[3]);

    delete[] data;
}

bool EraserTool::OnMouseMove(int x, int y) noexcept{
    if(isMouseDown){
        Coords curr(GetViewportWidth(), GetViewportHeight());
        curr.SetXWindows(x);
        curr.SetYWindows(y);
        ErseLine(prevMousePos, curr);
    }
    prevMousePos.SetXWindows(x);
    prevMousePos.SetYWindows(y);
    return true;
} 

bool EraserTool::OnLMouseDown(int x, int y) noexcept{
    isMouseDown = true;
    prevMousePos.SetXWindows(x);
    prevMousePos.SetYWindows(y);
    Erse(prevMousePos);
    return true;
}

bool EraserTool::OnLMouseUp(int x, int y) noexcept{
    if(isMouseDown){
        isMouseDown = false;
    }
    prevMousePos.SetXWindows(x);
    prevMousePos.SetYWindows(y);
    return true;
}

bool EraserTool::OnKeyDown(int vkCode, int repeat) noexcept{
    switch (vkCode)
    {
    case VK_OEM_6:{
        scale *= 1.0 + scaleIncrement;
        if(scale > scaleMax) scale = scaleMax;
    } return true;
    case VK_OEM_4:{
        scale *= 1.0 - scaleIncrement;
        if(scale < scaleMin) scale = scaleMin;  
    } return true;
    default: return false;
    }
}

bool EraserTool::OnKeyUp(int vkCode) noexcept{
    return false;
}

bool EraserTool::OnTextInput(std::wstring str) noexcept{
    return false;
}

bool EraserTool::OnScrollUp() noexcept{
    scale *= 1.0 + scaleIncrement;
        if(scale > scaleMax) scale = scaleMax;
    return true;
}

bool EraserTool::OnScrollDown() noexcept{
    scale *= 1.0 - scaleIncrement;
        if(scale < scaleMin) scale = scaleMin;  
    return true;
}


EraserTool::EraserTool(int cx, int cy, const Texture &bg, const Texture &state) noexcept
    :DrawingTool(cx, cy, bg, state), prevMousePos(cx, cy){
    
    glGenTextures(1, &erseTex);
    glBindTexture(GL_TEXTURE_2D, erseTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

EraserTool::~EraserTool() noexcept{
    glDeleteTextures(1, &erseTex);
}
