#pragma once
#include "Tools/SelectToolTool.hpp"
#include "Tools/SelectMenuToolNode.hpp"
#include "Tools/SelectActionToolNode.hpp"
#include "Tools/MouseHighlightTool.hpp"
#include "Tools/BrushTool.hpp"
#include "Tools/EraserTool.hpp"

class SelectToolMenuManager{
private:
    CommitHandler &commitHandler;
    GLuint bg;

    Texture emptyTexture;
    Texture MouseHighlightTexture;
    Texture BrushTexture;
    Texture EraserTexture;
    std::unique_ptr<SelectMenuToolNode> rootMenuNode;
        std::unique_ptr<SelectActionToolNode> mouseHighlightToolNode; 
        std::unique_ptr<SelectActionToolNode> brushToolNode; 
        std::unique_ptr<SelectActionToolNode> eraserToolNode; 


    std::unique_ptr<SelectToolTool> selectToolmenu;
    std::unique_ptr<MouseHighlightTool> mouseHighlightTool;
    std::unique_ptr<BrushTool> brushTool;
    std::unique_ptr<EraserTool> eraserTool;

    DrawingTool * currTool;

    void SetCurrTool(DrawingTool *tool) noexcept;
public:
    SelectToolMenuManager(CommitHandler &commitHandler, GLuint bg);
    void OpenToolMenu() noexcept;
    void OpenBrush() noexcept;
    void OpenEraser() noexcept;
    void OpenMouseHighlightTool() noexcept;
    DrawingTool &GetCurrTool() noexcept;
};
    