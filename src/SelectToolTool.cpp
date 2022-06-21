#include "SelectToolTool.hpp"

SelectToolTool::SelectToolTool(int cx, int cy, SelectToolNode &rootToolNode) noexcept
    :DrawingTool(cx, cy), rootNode(rootToolNode){
    currNode = &rootNode;
}

void SelectToolTool::OnDraw() const noexcept{
    currNode->DrawSelectToolMenu(GetViewportWidth(), GetViewportHeight(), nodeOver);
}

void SelectToolTool::OnResize(int cx, int cy) noexcept{

}

bool SelectToolTool::OnMouseMove(int x, int y) noexcept{
    return true;
}

bool SelectToolTool::OnLMouseDown(int x, int y) noexcept{
    return true;
}

bool SelectToolTool::OnLMouseUp(int x, int y) noexcept{
    return true;
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