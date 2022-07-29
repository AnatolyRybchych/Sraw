#pragma once 

#include <string>
#include <vector>
#include <math.h>
#include <memory>
#include <functional>
#include <stdexcept>
#include "ResourceProvider.hpp"

class SelectToolNode{
private:
    void DrawSelectToolMenuBG(int cx, int cy) const noexcept;

    GLuint VBOMenuBg;
    GLuint progMenuBg;

    GLint vertex_pPosMenuBg;
    GLint viewportPosMenuBg;
    GLint circle_scalePosMenuBg;

    GLuint VBOMenuItem;
    GLuint progMenuItem;

    GLint vertex_pPosMenuItem;
    GLint viewportPosMenuItem;
    GLint circle_scalePosMenuItem;
    GLint segment_countPosMenuItem;
    GLint segmentPosMenuItem;
    GLint is_mouse_overPosMenuItem;
    GLint alphaPosMenuItem;
    GLint texPosMenuItem;
protected:
    virtual void OnSelect() noexcept = 0;
    virtual const GLuint GetImage() const noexcept = 0;
    virtual const std::wstring &GetText() const noexcept = 0;
    virtual const std::vector<SelectToolNode *> &GetToolNodes() const noexcept = 0;
    virtual void Select() noexcept;
public:
    SelectToolNode() noexcept;

    static const float CircleScale;
    static const int MaxToolNodes;

    bool SelectNode(int id) const noexcept;
    int GetNodeIdByPoint(int cx, int cy, int x, int y) const noexcept;
    void Draw(int cx, int cy, int pos, bool mouseOver) noexcept;
    void DrawSelectToolMenu(int cx, int cy, int mouseOverTool) noexcept;

    virtual ~SelectToolNode() noexcept;
};