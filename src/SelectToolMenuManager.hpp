#pragma once
#include "SelectToolTool.hpp"
#include "SelectMenuToolNode.hpp"

class SelectToolMenuManager{
private:
    Texture emptyTexture;
    std::unique_ptr<SelectMenuToolNode> rootMenuNode;
    std::unique_ptr<DrawingTool> currTool;
    SelectToolTool *CreateSelectToolMenu(int cx, int cy);
public:
    SelectToolMenuManager();
    void OpenToolMenu() noexcept;
    DrawingTool &GetCurrTool() noexcept;
};
    