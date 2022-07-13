#pragma once
#include "Tools/SelectToolTool.hpp"
#include "Tools/SelectMenuToolNode.hpp"
#include "Tools/SelectActionToolNode.hpp"
#include "Tools/MouseHighlightTool.hpp"
#include "Tools/BrushTool.hpp"
#include "Tools/EraserTool.hpp"
#include "Tools/ColorPaletTool.hpp"

class SelectToolMenuManager{
private:
    CommitHandler &commitHandler;
    GLuint bg;

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

    std::unique_ptr<SelectMenuToolNode> rootMenuNode;
        std::unique_ptr<SelectActionToolNode> mouseHighlightToolNode; 
        std::unique_ptr<SelectActionToolNode> brushToolNode; 
        std::unique_ptr<SelectActionToolNode> eraserToolNode; 
        std::unique_ptr<SelectActionToolNode> colorPaletToolNode; 
        std::unique_ptr<SelectMenuToolNode> quitMenuNode;
            std::unique_ptr<SelectActionToolNode> clearNode; 
            std::unique_ptr<SelectActionToolNode> hideNode; 
            std::unique_ptr<SelectActionToolNode> saveToFileNode; 


    std::unique_ptr<SelectToolTool> selectToolmenu;
    std::unique_ptr<MouseHighlightTool> mouseHighlightTool;
    std::unique_ptr<BrushTool> brushTool;
    std::unique_ptr<EraserTool> eraserTool;
    std::unique_ptr<ColorPaletTool> colorPaletTool;

    DrawingTool * currTool;

    void SetCurrTool(DrawingTool *tool) noexcept;
public:
    SelectToolMenuManager(CommitHandler &commitHandler, GLuint bg);
    void OpenToolMenu() noexcept;
    void OpenQuitMenu() noexcept;
    void OpenBrush() noexcept;
    void OpenEraser() noexcept;
    void OpenColorPalette() noexcept;
    void OpenMouseHighlightTool() noexcept;
    DrawingTool &GetCurrTool() noexcept;
};
    