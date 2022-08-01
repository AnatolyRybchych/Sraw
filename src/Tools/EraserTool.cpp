#include "../ResourceProvider.hpp"
#include "EraserTool.hpp"
#include "../GlWrappers/ShaderProgram.hpp"
#include "../DrawImage.hpp"
#include "../Basics.hpp"

void EraserTool::Erse(int x, int y) const noexcept{
    glEnable(GL_SCISSOR_TEST);
    
    BindFramebuffer(GetState().GetGLID());
    glScissor(x - GetViewportWidth() * scale * 0.5, (GetViewportHeight() - y) - GetViewportWidth() * scale * 0.5, GetViewportWidth() * scale, GetViewportWidth() * scale);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    UnbindFramebuffer();
    
    glDisable(GL_SCISSOR_TEST);
}

void EraserTool::ErseLine(int x1, int y1, int x2, int y2) const noexcept{
    float step = sqrt(GetViewportWidth() * GetViewportWidth() + GetViewportHeight() * GetViewportHeight()) / (distance2(x1, y1, x2, y2)) * scale * 0.2;
    for(float progress = 0.0; progress < 1.0; progress += step){
        Erse(lerpi(x1, x2, progress), lerpi(y1, y2, progress));
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
        ErseLine(prevMousePos.GetXWindows(), prevMousePos.GetYWindows(), x, y);
    }
    prevMousePos.SetXWindows(x);
    prevMousePos.SetYWindows(y);
    return true;
} 

bool EraserTool::OnLMouseDown(int x, int y) noexcept{
    isMouseDown = true;
    prevMousePos.SetXWindows(x);
    prevMousePos.SetYWindows(y);
    Erse(x, y);
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
