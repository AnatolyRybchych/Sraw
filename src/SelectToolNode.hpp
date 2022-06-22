#pragma once 

#include "Texture.hpp"
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <stdexcept>
#include "ShaderProgram.hpp"

class SelectToolNode{
private:
    void DrawSelectToolMenuBG(int cx, int cy) const noexcept;

    GLuint VBO;
    GLuint prog;

    GLint vertex_pPos;
    GLint viewportPos;
    GLint circle_scalePos;
protected:
    virtual void OnSelect() noexcept = 0;
    virtual const GLuint GetImage() const noexcept = 0;
    virtual const std::wstring &GetText() const noexcept = 0;
    virtual const std::vector<SelectToolNode *> &GetToolNodes() const noexcept = 0;
public:
    SelectToolNode() noexcept;

    static const float CircleScale;
    static const int MaxToolNodes;

    virtual void Select() noexcept;
    void Draw(int cx, int cy, int pos, bool mouseOver) noexcept;
    void DrawSelectToolMenu(int cx, int cy, int mouseOverTool) noexcept;

    virtual ~SelectToolNode() noexcept;
};