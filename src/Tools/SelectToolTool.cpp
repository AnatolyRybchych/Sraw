#include "SelectToolTool.hpp"
#include <iostream>

SelectToolTool::SelectToolTool(int cx, int cy, CommitHandler &commitHandler, SelectToolNode &rootToolNode) noexcept
    :DrawingTool(cx, cy, commitHandler), rootNode(rootToolNode){
    currNode = &rootNode;
}

void SelectToolTool::OnDraw() const noexcept{
    currNode->DrawSelectToolMenu(GetViewportWidth(), GetViewportHeight(), nodeOver);
}

void SelectToolTool::OnDrawCommit() noexcept{

}

void SelectToolTool::OnResize(int cx, int cy) noexcept{

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
    currNode = node;
}
