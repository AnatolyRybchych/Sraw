#include "SelectToolMenuManager.hpp"
#include "Tools/MouseHighlightTool.hpp"
#include "ResourceProvider.hpp"


SelectToolMenuManager::SelectToolMenuManager(CommitHandler &commitHandler, int cx, int cy, const Texture &bg, Quitable &quitable)
    :emptyTexture((GLuint)0),
    MouseHighlightTexture(ResourceProvider::GetProvider().GetMouseHighlightIcon()),
    BrushTexture(ResourceProvider::GetProvider().GetBrushIcon()),
    EraserTexture(ResourceProvider::GetProvider().GetEraserIcon()),
    ColorPaletteTexture(ResourceProvider::GetProvider().GetColorPaletteIcon()),
    PaletteTexture(ResourceProvider::GetProvider().GetPalette()),
    QuitTexture(ResourceProvider::GetProvider().GetQuitIcon()),
    ClearTexture(ResourceProvider::GetProvider().GetClearIcon()),
    HideTexture(ResourceProvider::GetProvider().GetHideIcon()),
    SaveToFileTexture(ResourceProvider::GetProvider().GetSaveToFileIcon()),
    commitHandler(commitHandler),
    quitable(quitable),
    bg(bg){

    this->cx = cx;
    this->cy = cy;

    mouseHighlightToolNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            MouseHighlightTexture, 
            L"Mouse highlight", 
            std::bind(SelectToolMenuManager::OpenMouseHighlightTool, this)
        )
    );

    brushToolNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            BrushTexture, 
            L"Brush", 
            std::bind(SelectToolMenuManager::OpenBrush, this)
        )
    );

    eraserToolNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            EraserTexture, 
            L"Eraser", 
            std::bind(SelectToolMenuManager::OpenEraser, this)
        )
    );

    colorPaletToolNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            ColorPaletteTexture, 
            L"Color palette", 
            std::bind(SelectToolMenuManager::OpenColorPalette, this)
        )
    );

    clearNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            ClearTexture, 
            L"Clear canvas", 
            std::bind(Quitable::HideWindowAndResoreState, &quitable)
        )
    );

    hideNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            HideTexture, 
            L"Hide canvas", 
            std::bind(Quitable::HideWindow, &quitable)
        )
    );

    saveToFileNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            SaveToFileTexture, 
            L"Save to file", 
            std::bind(Quitable::HideWindowSaveStateToFile, &quitable)
        )
    );

    saveToClipboard = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            SaveToFileTexture, 
            L"Copy to clipboard", 
            std::bind(Quitable::HideWindowCopyStateToClipboard, &quitable)
        )
    );

    quitApp = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            QuitTexture, 
            L"Quit application", 
            std::bind(Quitable::QuitApp, &quitable)
        )
    );

    

    quitMenuNode = std::unique_ptr<SelectMenuToolNode>(
        new SelectMenuToolNode(
        std::vector<SelectToolNode*>{
            clearNode.get(),
            hideNode.get(),
            saveToFileNode.get(),
            saveToClipboard.get(),
            quitApp.get(),
        }, 
        L"Quit", 
        QuitTexture,
        std::bind(SelectToolMenuManager::OpenQuitMenu, this)
        )
    );

    rootMenuNode = std::unique_ptr<SelectMenuToolNode>(
        new SelectMenuToolNode(
        std::vector<SelectToolNode*>{
            mouseHighlightToolNode.get(),
            brushToolNode.get(),
            eraserToolNode.get(),
            colorPaletToolNode.get(),
            quitMenuNode.get(),
        }, 
        L"root", 
        emptyTexture)
    );

    mouseHighlightTool = std::unique_ptr<MouseHighlightTool>(new MouseHighlightTool(cx, cy, commitHandler, bg));
    colorPaletTool = std::unique_ptr<ColorPaletTool>(new ColorPaletTool(cx, cy, commitHandler, bg, PaletteTexture.GetGLID()));
    brushTool = std::unique_ptr<BrushTool>(new BrushTool(cx, cy, commitHandler, bg, *colorPaletTool.get()));
    eraserTool = std::unique_ptr<EraserTool>(new EraserTool(cx, cy, commitHandler, bg));
    selectToolmenu = std::unique_ptr<SelectToolTool>(new SelectToolTool(cx, cy, commitHandler, bg, *(SelectToolNode*)rootMenuNode.get()));

    currTool = mouseHighlightTool.get();
}

DrawingTool &SelectToolMenuManager::GetCurrTool() noexcept{
    return *currTool;
}

void SelectToolMenuManager::SetCurrTool(DrawingTool *tool) noexcept{
    int cx = currTool->GetViewportWidth();
    int cy = currTool->GetViewportHeight();
    currTool = tool;
}

void SelectToolMenuManager::OpenToolMenu() noexcept{
    selectToolmenu->SetCurrNode(nullptr);
    SetCurrTool(selectToolmenu.get());
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
