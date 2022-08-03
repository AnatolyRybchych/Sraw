#include "SelectToolMenuManager.hpp"
#include "Tools/MouseHighlightTool.hpp"
#include "ResourceProvider.hpp"


SelectToolMenuManager::SelectToolMenuManager(int cx, int cy, const Texture &bg, Quitable &quitable, const DrawingTarget &drawingTarget, const Texture &state)
    :emptyTexture((GLuint)0),
    quitable(quitable),
    drawingTarget(drawingTarget),
    state(state),
    bg(bg){

    this->cx = cx;
    this->cy = cy;

    brushToolNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            ResourceProvider::GetProvider().GetBrushTexture(),
            L"Brush", 
            std::bind(SelectToolMenuManager::OpenBrush, this)
        )
    );

    eraserToolNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            ResourceProvider::GetProvider().GetEraserTexture(),
            L"Eraser", 
            std::bind(SelectToolMenuManager::OpenEraser, this)
        )
    );

    colorPaletToolNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            ResourceProvider::GetProvider().GetColorPaletteTexture(),
            L"Color palette", 
            std::bind(SelectToolMenuManager::OpenColorPalette, this)
        )
    );

    clearNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            ResourceProvider::GetProvider().GetClearTexture(),
            L"Clear canvas", 
            std::bind(Quitable::HideWindowAndResoreState, &quitable)
        )
    );

    hideNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            ResourceProvider::GetProvider().GetHideTexture(),
            L"Hide canvas", 
            std::bind(Quitable::HideWindow, &quitable)
        )
    );

    saveToFileNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            ResourceProvider::GetProvider().GetSaveToFileTexture(),
            L"Save to file", 
            std::bind(Quitable::HideWindowSaveStateToFile, &quitable)
        )
    );

    saveToClipboardNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            ResourceProvider::GetProvider().GetCopyToClipboardTexture(),
            L"Copy to clipboard", 
            std::bind(Quitable::HideWindowCopyStateToClipboard, &quitable)
        )
    );

    quitAppNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            ResourceProvider::GetProvider().GetQuitTexture(),
            L"Quit application", 
            std::bind(Quitable::QuitApp, &quitable)
        )
    );

    mouseHighlightToolNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            ResourceProvider::GetProvider().GetMouseHighlightTexture(),
            L"Mouse highlight", 
            std::bind(SelectToolMenuManager::OpenMouseHighlightTool, this)
        )
    );

    textToolNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            ResourceProvider::GetProvider().GetTextTexture(),
            L"Text", 
            std::bind(SelectToolMenuManager::OpenText, this)
        )
    );

    selectionToolNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            ResourceProvider::GetProvider().GetSelectionTexture(),
            L"Selection", 
            std::bind(SelectToolMenuManager::OpenSelection, this)
        )
    );

    lineToolNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
        ResourceProvider::GetProvider().GetPrimitivesTexture(),
        L"Line", 
        std::bind(SelectToolMenuManager::OpenLineTool, this)
        )
    );  

    primitivesMenuNode = std::unique_ptr<SelectMenuToolNode>(
        new SelectMenuToolNode(
        std::vector<SelectToolNode*>{
            lineToolNode.get(),
        }, 
        L"Menu/Tools/Primitives", 
        ResourceProvider::GetProvider().GetPrimitivesTexture(),
        std::bind(SelectToolMenuManager::OpenTool_PrimitivesMenu, this)
        )
    );  

    startEndDiagramToolNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            ResourceProvider::GetProvider().GetBlockDiagramStartEndTexture(),
            L"Start | End", 
            std::bind(SelectToolMenuManager::OpenStartEndDiagram, this)
        )
    );

    actionDiagramToolNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            ResourceProvider::GetProvider().GetBlockDiagramTexture(),
            L"Action", 
            std::bind(SelectToolMenuManager::OpenActionDiagram, this)
        )
    );
    inOutDiagramToolNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            ResourceProvider::GetProvider().GetBlockDiagramInOutTexture(),
            L"Input | Output", 
            std::bind(SelectToolMenuManager::OpenInOutDiagram, this)
        )
    );
    funcDiagramToolNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            ResourceProvider::GetProvider().GetBlockDiagramFuncTexture(),
            L"Function", 
            std::bind(SelectToolMenuManager::OpenFuncDiagram, this)
        )
    );
    conditionDiagramToolNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            ResourceProvider::GetProvider().GetBlockDiagramConditionTexture(),
            L"Condition", 
            std::bind(SelectToolMenuManager::OpenConditionDiagram, this)
        )
    );

    blockDiagramToolNode = std::unique_ptr<SelectMenuToolNode>(
        new SelectMenuToolNode(
        std::vector<SelectToolNode*>{
            startEndDiagramToolNode.get(),
            actionDiagramToolNode.get(),
            conditionDiagramToolNode.get(),
            inOutDiagramToolNode.get(),
            funcDiagramToolNode.get(),
        }, 
        L"Menu/Tools/Block diagram", 
        ResourceProvider::GetProvider().GetBlockDiagramTexture(),
        std::bind(SelectToolMenuManager::OpenTool_BlockDiagramMenu, this)
        )
    ); 

    othersMenuNode = std::unique_ptr<SelectMenuToolNode>(
        new SelectMenuToolNode(
        std::vector<SelectToolNode*>{
            mouseHighlightToolNode.get(),
        }, 
        L"Menu/Tools/Others", 
        ResourceProvider::GetProvider().GetOthersTexture(),
        std::bind(SelectToolMenuManager::OpenTool_OthersMenu, this)
        )
    ); 

    toolsMenuNode = std::unique_ptr<SelectMenuToolNode>(
        new SelectMenuToolNode(
        std::vector<SelectToolNode*>{
            primitivesMenuNode.get(),
            textToolNode.get(),
            blockDiagramToolNode.get(),
            selectionToolNode.get(),
            othersMenuNode.get()
        }, 
        L"Menu/Tools", 
        ResourceProvider::GetProvider().GetToolsTexture(),
        std::bind(SelectToolMenuManager::OpenTool_ToolsMenu, this)
        )
    );    

    quitMenuNode = std::unique_ptr<SelectMenuToolNode>(
        new SelectMenuToolNode(
        std::vector<SelectToolNode*>{
            clearNode.get(),
            hideNode.get(),
            saveToFileNode.get(),
            saveToClipboardNode.get(),
            quitAppNode.get(),
        }, 
        L"Menu/Quit", 
        ResourceProvider::GetProvider().GetQuitTexture(),
        std::bind(SelectToolMenuManager::OpenQuitMenu, this)
        )
    );

    rootMenuNode = std::unique_ptr<SelectMenuToolNode>(
        new SelectMenuToolNode(
        std::vector<SelectToolNode*>{
            toolsMenuNode.get(),
            brushToolNode.get(),
            eraserToolNode.get(),
            colorPaletToolNode.get(),
            quitMenuNode.get(),
        }, 
        L"Menu", 
        emptyTexture)
    );


    mouseHighlightTool = std::unique_ptr<MouseHighlightTool>(new MouseHighlightTool(cx, cy, bg, state));
    colorPaletTool = std::unique_ptr<ColorPaletTool>(new ColorPaletTool(cx, cy, bg, state, ResourceProvider::GetProvider().GetPaletteTexture().GetGLID()));
    brushTool = std::unique_ptr<BrushTool>(new BrushTool(cx, cy, bg, state, *colorPaletTool.get()));
    eraserTool = std::unique_ptr<EraserTool>(new EraserTool(cx, cy, bg, state));
    textTool = std::unique_ptr<TextTool>(new TextTool(cx, cy, bg, state, *colorPaletTool.get()));
    selectionTool = std::unique_ptr<SelectionTool>(new SelectionTool(cx, cy, bg, state));

    diagamSettings = std::unique_ptr<BlockDiagramSetting>(new BlockDiagramSetting(*colorPaletTool.get(), 48));
    actionBlockDiagramTool = std::unique_ptr<ActionBlockDiagramTool>(new ActionBlockDiagramTool(cx, cy, bg, state, *diagamSettings.get()));
    conditionBlockDiagramTool = std::unique_ptr<ConditionBlockDiagramTool>(new ConditionBlockDiagramTool(cx, cy, bg, state, *diagamSettings.get()));
    startEndBlockDiagramTool = std::unique_ptr<StartEndBlockDiagramTool>(new StartEndBlockDiagramTool(cx, cy, bg, state, *diagamSettings.get()));
    inOutBlockDiagramTool = std::unique_ptr<InOutBlockDiagramTool>(new InOutBlockDiagramTool(cx, cy, bg, state, *diagamSettings.get()));
    funcBlockDiagramTool = std::unique_ptr<FuncBlockDiagramTool>(new FuncBlockDiagramTool(cx, cy, bg, state, *diagamSettings.get()));

    lineTool = std::unique_ptr<LineTool>(new LineTool(cx, cy, bg, state, *brushTool.get()));

    selectToolmenu = std::unique_ptr<SelectToolTool>(new SelectToolTool(cx, cy, bg, state, *(SelectToolNode*)rootMenuNode.get()));

    currTool = mouseHighlightTool.get();
}

DrawingTool &SelectToolMenuManager::GetCurrTool() noexcept{
    return *currTool;
}

void SelectToolMenuManager::SetCurrTool(DrawingTool *tool) noexcept{
    currTool = tool;
    drawingTarget.Redraw();
}

void SelectToolMenuManager::OpenToolMenu() noexcept{
    selectToolmenu->SetCurrNode(nullptr);
    SetCurrTool(selectToolmenu.get());
}

void SelectToolMenuManager::OpenTool_ToolsMenu() noexcept{
    selectToolmenu->SetCurrNode(toolsMenuNode.get());
}

void SelectToolMenuManager::OpenTool_PrimitivesMenu() noexcept{
    selectToolmenu->SetCurrNode(primitivesMenuNode.get());
}

void SelectToolMenuManager::OpenTool_BlockDiagramMenu() noexcept{
    selectToolmenu->SetCurrNode(blockDiagramToolNode.get());
}

void SelectToolMenuManager::OpenTool_OthersMenu() noexcept{
    selectToolmenu->SetCurrNode(othersMenuNode.get());
}

void SelectToolMenuManager::OpenQuitMenu() noexcept{
    selectToolmenu->SetCurrNode(quitMenuNode.get());
}

void SelectToolMenuManager::OpenBrush() noexcept{
    SetCurrTool(brushTool.get());
}

void SelectToolMenuManager::OpenEraser() noexcept{
    SetCurrTool(eraserTool.get());
}

void SelectToolMenuManager::OpenText() noexcept{
    SetCurrTool(textTool.get());
}

void SelectToolMenuManager::OpenSelection() noexcept{
    SetCurrTool(selectionTool.get());
}

void SelectToolMenuManager::OpenActionDiagram() noexcept{
    SetCurrTool(actionBlockDiagramTool.get());
}

void SelectToolMenuManager::OpenConditionDiagram() noexcept{
    SetCurrTool(conditionBlockDiagramTool.get());
}

void SelectToolMenuManager::OpenStartEndDiagram() noexcept{
    SetCurrTool(startEndBlockDiagramTool.get());
}

void SelectToolMenuManager::OpenInOutDiagram() noexcept{
    SetCurrTool(inOutBlockDiagramTool.get());
}

void SelectToolMenuManager::OpenFuncDiagram() noexcept{
    SetCurrTool(funcBlockDiagramTool.get());
}

void SelectToolMenuManager::OpenColorPalette() noexcept{
    SetCurrTool(colorPaletTool.get());
}
void SelectToolMenuManager::OpenMouseHighlightTool() noexcept{
    SetCurrTool(mouseHighlightTool.get());
}

void SelectToolMenuManager::OpenLineTool() noexcept{
    SetCurrTool(lineTool.get());
}

