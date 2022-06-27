#pragma once
#include "Tools/SelectToolTool.hpp"
#include "Tools/SelectMenuToolNode.hpp"
#include "Tools/SelectActionToolNode.hpp"
#include "Tools/MouseHighlightTool.hpp"
#include "Tools/BrushTool.hpp"

class SelectToolMenuManager{
private:
    CommitHandler &commitHandler;

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
    SelectToolMenuManager(CommitHandler &commitHandler);
    void OpenToolMenu() noexcept;
    void OpenBrush() noexcept;
    void OpenMouseHighlightTool() noexcept;
    DrawingTool &GetCurrTool() noexcept;
};
    