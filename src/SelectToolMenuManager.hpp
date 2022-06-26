#pragma once
#include "SelectToolTool.hpp"
#include "SelectMenuToolNode.hpp"
#include "SelectActionToolNode.hpp"
#include "MouseHighlightTool.hpp"
#include "BrushTool.hpp"

class SelectToolMenuManager{
private:
    Texture emptyTexture;
    Texture MouseHighlightTexture;
    Texture BrushTexture;
    std::unique_ptr<SelectMenuToolNode> rootMenuNode;
        std::unique_ptr<SelectActionToolNode> mouseHighlightToolNode; 
        std::unique_ptr<SelectActionToolNode> brushToolNode; 


    std::unique_ptr<SelectToolTool> selectToolmenu;
    std::unique_ptr<MouseHighlightTool> mouseHighlightTool;
    std::unique_ptr<BrushTool> brushTool;

    DrawingTool * currTool;

    void SetCurrTool(DrawingTool *tool) noexcept;
public:
    SelectToolMenuManager();
    void OpenToolMenu() noexcept;
    void OpenBrush() noexcept;
    void OpenMouseHighlightTool() noexcept;
    DrawingTool &GetCurrTool() noexcept;
};
    