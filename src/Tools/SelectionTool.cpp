#include "SelectionTool.hpp"
#include "../DrawImage.hpp"
#include "../RectRenderer.hpp"

Selection::Selection() noexcept{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Selection::~Selection() noexcept{
    glDeleteTextures(1, &texture);
}

void Selection::CopyContentFromTexture(GLuint texture, int x, int y, int cx, int cy) noexcept{
    if(cx < 0){ x += cx; cx = -cx;}
    if(cy < 0){ y += cy; cy = -cy;}
    if(x < 0) {x = 0;}
    if(y < 0) {y = 0;}

    srcX = x;
    srcY = y;
    srcCx = cx;
    srcCy = cy;
    char *data = new char[cx * cy * 4];
    fb.Bind();
    fb.AttachTexture2D(texture);
    glReadPixels(x, y, cx, cy, GL_RGBA, GL_UNSIGNED_BYTE, data);
    fb.Unbind();

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cx, cy, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);

    delete[] data;
}

void Selection::UnsetContent() noexcept{
    hasContent = false;
}

void Selection::DrawStretch(int x, int y, int cx, int cy) const noexcept{
    if(cx < 0){ x += cx; cx = -cx;}
    if(cy < 0){ y += cy; cy = -cy;}
    if(x < 0) {x = 0;}
    if(y < 0) {y = 0;}

    if(HasContent()){
        int vp[4];
        glGetIntegerv(GL_VIEWPORT, vp);

        glViewport(x, y, cx, cy);
        DrawImage::GetRenderer().Draw(texture);
        glViewport(vp[0], vp[1], vp[2], vp[3]);
    }
}

int Selection::GetSrcX() const noexcept{
    return srcX;
}

int Selection::GetSrcY() const noexcept{
    return srcY;
}

int Selection::GetSrcCx() const noexcept{
    return srcCx;
}

int Selection::GetSrcCy() const noexcept{
    return srcCy;
}


bool Selection::HasContent() const noexcept{
    return hasContent;
}

SelectionTool::SelectionTool(int cx, int cy, CommitHandler &commitHandler, const Texture &bg)
:DrawingTool(cx, cy, commitHandler, bg), p1(cx, cy), p2(cx, cy){
};

void SelectionTool::OnDraw() const noexcept{
    if(isMouseDown || isSelected){
        RectRenderer::GetRenderer().Fill(p1, p2, 0.6666, 0.6666, 1.0, 0.3);
    }
}

bool SelectionTool::OnMouseMove(int x, int y) noexcept{
    if(isMouseDown && !isSelected){
        p2.SetXWindows(x);
        p2.SetYWindows(y);

        return true;
    }
    return false;
} 

bool SelectionTool::OnLMouseDown(int x, int y) noexcept{
    isMouseDown = true;
    this->p1.SetXWindows(x);
    this->p2.SetXWindows(x);
    this->p1.SetYWindows(y);
    this->p2.SetYWindows(y);
    return false;
}

bool SelectionTool::OnLMouseUp(int x, int y) noexcept{
    if(isSelected){
           
        isSelected = false;
        return true;
    }
    if(isMouseDown){
        isMouseDown = false;
        isSelected = true;
    }
    
    return false;
}

bool SelectionTool::OnKeyDown(int vkCode, int repeat) noexcept{
    return false;
}

bool SelectionTool::OnKeyUp(int vkCode) noexcept{
    return false;
}   

bool SelectionTool::OnTextInput(std::wstring str) noexcept{
    return false;
}

bool SelectionTool::OnScrollUp() noexcept{
    return false;
}

bool SelectionTool::OnScrollDown() noexcept{
    return false;
}
