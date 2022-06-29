#include "SelectToolMenuManager.hpp"
#include "Tools/MouseHighlightTool.hpp"
#include "ResourceProvider.hpp"


SelectToolMenuManager::SelectToolMenuManager(CommitHandler &commitHandler, GLuint bg)
    :emptyTexture((GLuint)0),
    commitHandler(commitHandler),
    MouseHighlightTexture(ResourceProvider::GetProvider().GetMouseHighlightIcon()),
    BrushTexture(ResourceProvider::GetProvider().GetBrushIcon()),
    EraserTexture(ResourceProvider::GetProvider().GetEraserIcon()),
    bg(bg){

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

    rootMenuNode = std::unique_ptr<SelectMenuToolNode>(
        new SelectMenuToolNode(
        std::vector<SelectToolNode*>{
            mouseHighlightToolNode.get(),
            brushToolNode.get(),
            eraserToolNode.get(),
            mouseHighlightToolNode.get(),
            mouseHighlightToolNode.get(),
        }, 
        L"root", 
        emptyTexture)
    );

    mouseHighlightTool = std::unique_ptr<MouseHighlightTool>(new MouseHighlightTool(100, 100, commitHandler));
    brushTool = std::unique_ptr<BrushTool>(new BrushTool(100, 100, commitHandler));
    eraserTool = std::unique_ptr<EraserTool>(new EraserTool(100, 100, commitHandler, bg));
    selectToolmenu = std::unique_ptr<SelectToolTool>(new SelectToolTool(100, 100, commitHandler, *(SelectToolNode*)rootMenuNode.get()));

    currTool = mouseHighlightTool.get();
}

DrawingTool &SelectToolMenuManager::GetCurrTool() noexcept{
    return *currTool;
}

void SelectToolMenuManager::SetCurrTool(DrawingTool *tool) noexcept{
    int cx = currTool->GetViewportWidth();
    int cy = currTool->GetViewportHeight();
    currTool = tool;
    currTool->Resize(cx, cy);
}

void SelectToolMenuManager::OpenToolMenu() noexcept{
    SetCurrTool(selectToolmenu.get());
}

void SelectToolMenuManager::OpenBrush() noexcept{
    SetCurrTool(brushTool.get());
}

void SelectToolMenuManager::OpenEraser() noexcept{
    SetCurrTool(eraserTool.get());
}

void SelectToolMenuManager::OpenMouseHighlightTool() noexcept{
    SetCurrTool(mouseHighlightTool.get());
}
