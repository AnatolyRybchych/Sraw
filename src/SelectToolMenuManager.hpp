#pragma once
#include "Tools/SelectToolTool.hpp"
#include "Tools/SelectMenuToolNode.hpp"
#include "Tools/SelectActionToolNode.hpp"
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
    Texture MouseHighlightTexture;
    Texture BrushTexture;
    Texture EraserTexture;
    Texture ColorPaletteTexture;
    Texture PaletteTexture;
    Texture QuitTexture;
    Texture ClearTexture;
    Texture HideTexture;
    Texture SaveToFileTexture;
    Texture CopyToClipboardTexture;
    Texture ToolsTexture;

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
            std::unique_ptr<SelectActionToolNode> mouseHighlightToolNode; 
            //shapes tools menu
                //fill rectangle tool
                //rectangle tool
                //elipse tool
                //fill elipse tool
                //line tool
            //text stamp tool
            //block diagram shapes menu
                //action
                //condition
                //arrow
                //input
                //output
            //simple math diagram

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
    void OpenQuitMenu() noexcept;
    void OpenBrush() noexcept;
    void OpenEraser() noexcept;
    void OpenColorPalette() noexcept;
    void OpenMouseHighlightTool() noexcept;
    DrawingTool &GetCurrTool() noexcept;
};
    