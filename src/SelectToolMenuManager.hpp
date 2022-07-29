#pragma once
#include "Tools/SelectToolTool.hpp"
#include "SelectMenuToolNode.hpp"
#include "SelectActionToolNode.hpp"
#include "Tools/MouseHighlightTool.hpp"
#include "Tools/BrushTool.hpp"
#include "Tools/EraserTool.hpp"
#include "Tools/ColorPaletTool.hpp"
#include "Quitable.hpp"

class SelectToolMenuManager{
private:
    Quitable &quitable;
    CommitHandler &commitHandler;
    const Texture &bg;

    int cx, cy;

    Texture emptyTexture;

    std::unique_ptr<SelectMenuToolNode> rootMenuNode;
        std::unique_ptr<SelectActionToolNode> brushToolNode; 
        std::unique_ptr<SelectActionToolNode> eraserToolNode; 
        std::unique_ptr<SelectActionToolNode> colorPaletToolNode; 
        std::unique_ptr<SelectMenuToolNode> quitMenuNode;
            std::unique_ptr<SelectActionToolNode> clearNode; 
            std::unique_ptr<SelectActionToolNode> hideNode; 
            std::unique_ptr<SelectActionToolNode> saveToFileNode; 
            std::unique_ptr<SelectActionToolNode> saveToClipboardNode; 
            std::unique_ptr<SelectActionToolNode> quitAppNode; 
        std::unique_ptr<SelectMenuToolNode> toolsMenuNode;
            std::unique_ptr<SelectMenuToolNode> primitivesMenuNode;
            std::unique_ptr<SelectActionToolNode> textToolNode; 
            std::unique_ptr<SelectMenuToolNode> blockDiagramToolNode; 
            std::unique_ptr<SelectMenuToolNode> othersMenuNode;
                std::unique_ptr<SelectActionToolNode> mouseHighlightToolNode; 

    std::unique_ptr<SelectToolTool> selectToolmenu;
    std::unique_ptr<MouseHighlightTool> mouseHighlightTool;
    std::unique_ptr<BrushTool> brushTool;
    std::unique_ptr<EraserTool> eraserTool;
    std::unique_ptr<ColorPaletTool> colorPaletTool;

    DrawingTool * currTool;

    void SetCurrTool(DrawingTool *tool) noexcept;
public:
    SelectToolMenuManager(CommitHandler &commitHandler, int cx, int cy, const Texture &bg, Quitable &quitable);
    void OpenToolMenu() noexcept;
    void OpenTool_ToolsMenu() noexcept;
    void OpenTool_PrimitivesMenu() noexcept;
    void OpenTool_BlockDiagramMenu() noexcept;
    void OpenTool_OthersMenu() noexcept;
    void OpenQuitMenu() noexcept;
    void OpenBrush() noexcept;
    void OpenEraser() noexcept;
    void OpenColorPalette() noexcept;
    void OpenMouseHighlightTool() noexcept;
    DrawingTool &GetCurrTool() noexcept;
};
    