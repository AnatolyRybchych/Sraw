#include "SelectToolTool.hpp"
#include <iostream>

SelectToolTool::SelectToolTool(int cx, int cy, const Texture &bg, const Texture &state, SelectToolNode &rootToolNode) noexcept
    :DrawingTool(cx, cy, bg, state), rootNode(rootToolNode){
    currNode = &rootNode;
}

void SelectToolTool::OnDraw() const noexcept{
    currNode->DrawSelectToolMenu(GetViewportWidth(), GetViewportHeight(), nodeOver);
}

bool SelectToolTool::OnMouseMove(int x, int y) noexcept{
    int node = currNode->GetNodeIdByPoint(GetViewportWidth(), GetViewportHeight(), x, y);

    if(nodeOver != node){
        nodeOver = node;
        return true;
    }

    return false;
}

bool SelectToolTool::OnLMouseDown(int x, int y) noexcept{
    return currNode->SelectNode(currNode->GetNodeIdByPoint(GetViewportWidth(), GetViewportHeight(), x, y));
}

bool SelectToolTool::OnLMouseUp(int x, int y) noexcept{
    return false;
}

bool SelectToolTool::OnKeyDown(int vkCode, int repeat) noexcept{
    return false;
}

bool SelectToolTool::OnKeyUp(int vkCode) noexcept{
    return false;
}

bool SelectToolTool::OnTextInput(std::wstring str) noexcept{
    return false;
}

bool SelectToolTool::OnScrollUp() noexcept{
    return false;
}

bool SelectToolTool::OnScrollDown() noexcept{
    return false;
}

void SelectToolTool::SetCurrNode(SelectToolNode *node) noexcept{
    if(node)
        currNode = node;
    else
        currNode = &rootNode;
}
