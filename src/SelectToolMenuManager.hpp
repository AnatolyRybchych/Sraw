#pragma once
#include "Tools/SelectToolTool.hpp"
#include "SelectMenuToolNode.hpp"
#include "SelectActionToolNode.hpp"
#include "Tools/MouseHighlightTool.hpp"
#include "Tools/BrushTool.hpp"
#include "Tools/EraserTool.hpp"
#include "Tools/TextTool.hpp"
#include "Tools/SelectionTool.hpp"
#include "Tools/ColorPaletTool.hpp"
#include "Tools/ActionBlockDiagramTool.hpp"
#include "Tools/ConditionBlockDiagramTool.hpp"
#include "Tools/StartEndBlockDiagramTool.hpp"
#include "Tools/InOutBlockDiagramTool.hpp"
#include "Tools/FuncBlockDiagramTool.hpp"
#include "Tools/LineTool.hpp"
#include "Quitable.hpp"
#include "DrawingTarget.hpp"

class SelectToolMenuManager{
private:
    Quitable &quitable;
    const DrawingTarget &drawingTarget;
    const Texture &bg;
    const Texture &state;

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
                std::unique_ptr<SelectActionToolNode> lineToolNode; 
            std::unique_ptr<SelectActionToolNode> textToolNode; 
            std::unique_ptr<SelectMenuToolNode> blockDiagramToolNode; 
                std::unique_ptr<SelectActionToolNode> actionDiagramToolNode; 
                std::unique_ptr<SelectActionToolNode> conditionDiagramToolNode; 
                std::unique_ptr<SelectActionToolNode> startEndDiagramToolNode; 
                std::unique_ptr<SelectActionToolNode> inOutDiagramToolNode; 
                std::unique_ptr<SelectActionToolNode> funcDiagramToolNode; 
            std::unique_ptr<SelectActionToolNode> selectionToolNode; 
            std::unique_ptr<SelectMenuToolNode> othersMenuNode;
                std::unique_ptr<SelectActionToolNode> mouseHighlightToolNode; 

    std::unique_ptr<SelectToolTool> selectToolmenu;
    std::unique_ptr<MouseHighlightTool> mouseHighlightTool;
    std::unique_ptr<BrushTool> brushTool;
    std::unique_ptr<EraserTool> eraserTool;
    std::unique_ptr<ColorPaletTool> colorPaletTool;
    std::unique_ptr<TextTool> textTool;
    std::unique_ptr<SelectionTool> selectionTool;

    std::unique_ptr<BlockDiagramSetting> diagamSettings;
    std::unique_ptr<ActionBlockDiagramTool> actionBlockDiagramTool;
    std::unique_ptr<ConditionBlockDiagramTool> conditionBlockDiagramTool;
    std::unique_ptr<StartEndBlockDiagramTool> startEndBlockDiagramTool;
    std::unique_ptr<InOutBlockDiagramTool> inOutBlockDiagramTool;
    std::unique_ptr<FuncBlockDiagramTool> funcBlockDiagramTool;
    std::unique_ptr<LineTool> lineTool;

    DrawingTool * currTool;

    void SetCurrTool(DrawingTool *tool) noexcept;
public:
    SelectToolMenuManager(int cx, int cy, const Texture &bg, Quitable &quitable, const DrawingTarget &drawingTarget, const Texture &state);
    void OpenToolMenu() noexcept;
    void OpenTool_ToolsMenu() noexcept;
    void OpenTool_PrimitivesMenu() noexcept;
    void OpenTool_BlockDiagramMenu() noexcept;
    void OpenTool_OthersMenu() noexcept;
    void OpenQuitMenu() noexcept;
    void OpenBrush() noexcept;
    void OpenEraser() noexcept;
    void OpenText() noexcept;
    void OpenSelection() noexcept;
    void OpenActionDiagram() noexcept;
    void OpenConditionDiagram() noexcept;
    void OpenStartEndDiagram() noexcept;
    void OpenInOutDiagram() noexcept;
    void OpenFuncDiagram() noexcept;
    void OpenColorPalette() noexcept;
    void OpenMouseHighlightTool() noexcept;
    void OpenLineTool() noexcept;
    DrawingTool &GetCurrTool() noexcept;
};
    