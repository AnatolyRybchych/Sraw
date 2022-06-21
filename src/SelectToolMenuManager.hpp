#pragma once
#include "SelectToolTool.hpp"
#include "SelectMenuToolNode.hpp"

class SelectToolMenuManager{
private:
    Texture emptyTexture;
    std::unique_ptr<SelectMenuToolNode> rootMenuNode;
public:
    SelectToolMenuManager();

    SelectToolTool *CreateSelectToolMenu(int cx, int cy);
};