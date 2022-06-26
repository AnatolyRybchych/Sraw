#pragma once
#include "SelectToolTool.hpp"
#include "SelectMenuToolNode.hpp"
#include "SelectActionToolNode.hpp"
#include "MouseHighlightTool.hpp"

class SelectToolMenuManager{
private:
    Texture emptyTexture;
    Texture MouseHighlightTexture;
    std::unique_ptr<SelectMenuToolNode> rootMenuNode;
        std::unique_ptr<SelectActionToolNode> mouseHighlightToolNode; 


    std::unique_ptr<SelectToolTool> selectToolmenu;
    std::unique_ptr<MouseHighlightTool> mouseHighlightTool;

    DrawingTool * currTool;

    void SetCurrTool(DrawingTool *tool) noexcept;
public:
    SelectToolMenuManager();
    void OpenToolMenu() noexcept;
    void OpenMouseHighlightTool() noexcept;
    DrawingTool &GetCurrTool() noexcept;
};
    