#include "SelectionTool.hpp"
#include "../DrawImage.hpp"
#include "../RectRenderer.hpp"

enum stage{
    STAGE_WAITING,
    STAGE_SELECTING,
    STAGE_SELECTED,
    STAGE_MOVING,
};

int SelectionTool::GetSelectionX() const noexcept{
    int p1x = p1.GetXGlPixels();
    int p2x = p2.GetXGlPixels();
    return p1x > p2x ? p2x : p1x;
}

int SelectionTool::GetSelectionY() const noexcept{
    int p1y = p1.GetYGlPixels();
    int p2y = p2.GetYGlPixels();
    return p1y > p2y ? p2y : p1y;
}

int SelectionTool::GetSelectionCx() const noexcept{
    int p1x = p1.GetXGlPixels();
    int p2x = p2.GetXGlPixels();
    return p1x > p2x ? (p1x - p2x) : (p2x - p1x);
}

int SelectionTool::GetSelectionCy() const noexcept{
    int p1y = p1.GetYGlPixels();
    int p2y = p2.GetYGlPixels();
    return p1y > p2y ? (p1y - p2y) : (p2y - p1y);
}

bool SelectionTool::IsPointInSelectionRect(int x, int y) const noexcept{
    int sx = GetSelectionX();
    int sy = GetSelectionY();
    return sx < x && sy < y && sx + GetSelectionCx() > x && sy + GetSelectionCy() > y;
}

void SelectionTool::CopyStateToSelection(int x, int y, int cx, int cy) noexcept{
    glBindTexture(GL_TEXTURE_2D, selection);
    char *data = new char[cx * cy * 4];
    BindFramebuffer(GetState().GetGLID());
    glReadPixels(x, y, cx, cy, GL_RGBA, GL_UNSIGNED_BYTE, data);
    UnbindFramebuffer();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cx, cy, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    delete[] data;
    glBindTexture(GL_TEXTURE_2D, 0);
}

void SelectionTool::ErseRgn(int x, int y, int cx, int cy) noexcept{
    glEnable(GL_SCISSOR_TEST);
    
    BindFramebuffer(GetState().GetGLID());
    int vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    glScissor(x, y, cx, cy);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    UnbindFramebuffer();
    glDisable(GL_SCISSOR_TEST);
}

void SelectionTool::PasteSelection(int x, int y, int cx, int cy) noexcept{
    BindFramebuffer(GetState().GetGLID());
    int vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    glViewport(x, y, cx, cy);
    DrawImage::GetRenderer().Draw(selection);
    glViewport(vp[0], vp[1], vp[2], vp[3]);
    UnbindFramebuffer();
}

SelectionTool::SelectionTool(int cx, int cy, const Texture &bg, const Texture &state)
:DrawingTool(cx, cy, bg, state), p1(cx, cy), p2(cx, cy), lastMousePos(cx, cy){
    stage = STAGE_WAITING;
    glGenTextures(1, &selection);
    glGenTextures(1, &erseBuffer);
    glBindTexture(GL_TEXTURE_2D, selection);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, erseBuffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
};

SelectionTool::~SelectionTool(){
    glDeleteTextures(1, &selection);
    glDeleteTextures(1, &erseBuffer);
}

void SelectionTool::OnDraw() const noexcept{
    if(stage == STAGE_SELECTED || stage == STAGE_MOVING || stage == STAGE_SELECTING){
        if(stage != STAGE_SELECTING){
            int vp[4];
            glGetIntegerv(GL_VIEWPORT, vp);
            glViewport(GetSelectionX(), GetSelectionY(), GetSelectionCx(), GetSelectionCy());
            DrawImage::GetRenderer().Draw(selection);
            glViewport(vp[0], vp[1], vp[2], vp[3]);
        }
        if(IsPointInSelectionRect(lastMousePos.GetXGlPixels(), lastMousePos.GetYGlPixels()))
            RectRenderer::GetRenderer().Fill(p1, p2, 0.6666, 0.6666, 1.0, 0.1);
        else 
            RectRenderer::GetRenderer().Fill(p1, p2, 0.6666, 0.6666, 1.0, 0.3);
    }
}

bool SelectionTool::OnMouseMove(int x, int y) noexcept{
    bool ret = false;
    switch(stage){
        case STAGE_WAITING:{
        } break;
        case STAGE_SELECTING:{
            p2.SetXWindows(x);
            p2.SetYWindows(y);
            ret = true;
        } break;
        case STAGE_SELECTED:{
            ret = true;
        } break;
        case STAGE_MOVING:{
            int offsetX = x - lastMousePos.GetXWindows();
            int offsetY = y - lastMousePos.GetYWindows();

            p1.SetXWindows(p1.GetXWindows() + offsetX);
            p1.SetYWindows(p1.GetYWindows() + offsetY);
            p2.SetXWindows(p2.GetXWindows() + offsetX);
            p2.SetYWindows(p2.GetYWindows() + offsetY);
            ret = true;
        } break;
    };

    lastMousePos.SetXWindows(x);
    lastMousePos.SetYWindows(y);
    return ret;
} 

bool SelectionTool::OnLMouseDown(int x, int y) noexcept{
    bool ret = false;
    switch(stage){
        case STAGE_WAITING:{
            p1.SetXWindows(x);
            p1.SetYWindows(y);
            p2.SetXWindows(x);
            p2.SetYWindows(y);

            stage = STAGE_SELECTING;
            ret = true;
        } break;
        case STAGE_SELECTING:{
            p2.SetXWindows(x);
            p2.SetYWindows(y);

            ret = true;
        } break;
        case STAGE_SELECTED:{
            if(IsPointInSelectionRect(x, GetViewportHeight() - y)){
                stage = STAGE_MOVING;
                if(!isControlDown){
                    CopyStateToSelection(GetSelectionX(), GetSelectionY(), GetSelectionCx(), GetSelectionCy());
                    ErseRgn(GetSelectionX(), GetSelectionY(), GetSelectionCx(), GetSelectionCy());
                }
                ret = true;
            }
            else{
                stage = STAGE_WAITING;
                ret = true;
            }
        } break;
        case STAGE_MOVING:{
        } break;
    };

    lastMousePos.SetXWindows(x);
    lastMousePos.SetYWindows(y);
    return ret;
}

bool SelectionTool::OnLMouseUp(int x, int y) noexcept{
    bool ret = true;

    switch(stage){
        case STAGE_WAITING:{
           
        } break;
        case STAGE_SELECTING:{
            CopyStateToSelection(GetSelectionX(), GetSelectionY(), GetSelectionCx(), GetSelectionCy());
            stage = STAGE_SELECTED;
        } break;
        case STAGE_SELECTED:{

        } break;
        case STAGE_MOVING:{
            PasteSelection(GetSelectionX(), GetSelectionY(), GetSelectionCx(), GetSelectionCy());
            stage = STAGE_SELECTED;
            ret = true;
        } break;
    };

    lastMousePos.SetXWindows(x);
    lastMousePos.SetYWindows(y);
    return ret;
}

bool SelectionTool::OnKeyDown(int vkCode, int repeat) noexcept{
    switch (vkCode){
    case VK_CONTROL:
    case VK_LCONTROL:
    case VK_RCONTROL:{
        isControlDown = true;
    } return false;
    case VK_DELETE:{
        if(stage == STAGE_SELECTED){
            stage = STAGE_WAITING;
            ErseRgn(GetSelectionX(), GetSelectionY(), GetSelectionCx(), GetSelectionCy());
        }
    } return true;
    }
    return false;
}

bool SelectionTool::OnKeyUp(int vkCode) noexcept{
    switch (vkCode){
    case VK_CONTROL:
    case VK_LCONTROL:
    case VK_RCONTROL:{
        isControlDown = false;
    } return false;
    case VK_RETURN:{
        stage = STAGE_WAITING;
    }return true;
    }
    return false;
}   

bool SelectionTool::OnTextInput(std::wstring str) noexcept{
    return false;
}

bool SelectionTool::OnScrollUp() noexcept{
    if(stage == STAGE_MOVING){

        float scale = 0.95;

        float scale_2 = scale * 0.5;

        int x = GetSelectionX();
        int y = GetSelectionY();
        int cx = GetSelectionCx();
        int cy = GetSelectionCy();

        int selectionCenterX = x + cx / 2;
        int selectionCenterY = y + cy / 2;

        p1.SetXGlPixels(selectionCenterX - cx * scale_2);
        p1.SetYGlPixels(selectionCenterY - cy * scale_2);
        p2.SetXGlPixels(selectionCenterX + cx * scale_2);
        p2.SetYGlPixels(selectionCenterY + cy * scale_2);

        return true;
    }
    return false;
}

bool SelectionTool::OnScrollDown() noexcept{
    if(stage == STAGE_MOVING){
        float scale = 1.05;

        float scale_2 = scale * 0.5;

        int x = GetSelectionX();
        int y = GetSelectionY();
        int cx = GetSelectionCx();
        int cy = GetSelectionCy();

        double selectionCenterX = x + cx / 2.0;
        double selectionCenterY = y + cy / 2.0;

        p1.SetXGlPixels(selectionCenterX - cx * scale_2);
        p1.SetYGlPixels(selectionCenterY - cy * scale_2);
        p2.SetXGlPixels(selectionCenterX + cx * scale_2);
        p2.SetYGlPixels(selectionCenterY + cy * scale_2);
        return true;
    }
    return false;
}
