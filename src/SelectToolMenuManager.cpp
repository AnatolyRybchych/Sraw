#include "SelectToolMenuManager.hpp"
#include "Tools/MouseHighlightTool.hpp"
#include "ResourceProvider.hpp"


SelectToolMenuManager::SelectToolMenuManager(CommitHandler &commitHandler, int cx, int cy, const Texture &bg, Quitable &quitable)
    :emptyTexture((GLuint)0),
    commitHandler(commitHandler),
    quitable(quitable),
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
            std::bind(SelectToolMenuManager::OpenMouseHighlightTool, this)
        )
    );

    mouseHighlightToolNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            ResourceProvider::GetProvider().GetMouseHighlightTexture(),
            L"Mouse highlight", 
            std::bind(SelectToolMenuManager::OpenMouseHighlightTool, this)
        )
    );

    primitivesMenuNode = std::unique_ptr<SelectMenuToolNode>(
        new SelectMenuToolNode(
        std::vector<SelectToolNode*>{
        }, 
        L"Menu/Tools/Primitives", 
        ResourceProvider::GetProvider().GetPrimitivesTexture(),
        std::bind(SelectToolMenuManager::OpenTool_PrimitivesMenu, this)
        )
    );  

    blockDiagramToolNode = std::unique_ptr<SelectMenuToolNode>(
        new SelectMenuToolNode(
        std::vector<SelectToolNode*>{
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

    mouseHighlightTool = std::unique_ptr<MouseHighlightTool>(new MouseHighlightTool(cx, cy, commitHandler, bg));
    colorPaletTool = std::unique_ptr<ColorPaletTool>(new ColorPaletTool(cx, cy, commitHandler, bg, ResourceProvider::GetProvider().GetPaletteTexture().GetGLID()));
    brushTool = std::unique_ptr<BrushTool>(new BrushTool(cx, cy, commitHandler, bg, *colorPaletTool.get()));
    eraserTool = std::unique_ptr<EraserTool>(new EraserTool(cx, cy, commitHandler, bg));
    selectToolmenu = std::unique_ptr<SelectToolTool>(new SelectToolTool(cx, cy, commitHandler, bg, *(SelectToolNode*)rootMenuNode.get()));

    currTool = mouseHighlightTool.get();
}

DrawingTool &SelectToolMenuManager::GetCurrTool() noexcept{
    return *currTool;
}

void SelectToolMenuManager::SetCurrTool(DrawingTool *tool) noexcept{
    currTool = tool;
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

void SelectToolMenuManager::OpenColorPalette() noexcept{
    SetCurrTool(colorPaletTool.get());
}

void SelectToolMenuManager::OpenMouseHighlightTool() noexcept{
    SetCurrTool(mouseHighlightTool.get());
}
