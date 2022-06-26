#include "SelectToolMenuManager.hpp"
#include "MouseHighlightTool.hpp"
#include "ResourceProvider.hpp"


SelectToolMenuManager::SelectToolMenuManager()
    :emptyTexture((GLuint)0),
    MouseHighlightTexture(ResourceProvider::GetProvider().GetMouseHighlightIcon()){

    mouseHighlightToolNode = std::unique_ptr<SelectActionToolNode>(
        new SelectActionToolNode(
            MouseHighlightTexture, 
            L"Mouse highlight", 
            std::bind(SelectToolMenuManager::OpenMouseHighlightTool, this)
        )
    );

    rootMenuNode = std::unique_ptr<SelectMenuToolNode>(
        new SelectMenuToolNode(
        std::vector<SelectToolNode*>{
            mouseHighlightToolNode.get()
        }, 
        L"root", 
        emptyTexture)
    );

    mouseHighlightTool = std::unique_ptr<MouseHighlightTool>(new MouseHighlightTool(100, 100));
    selectToolmenu = std::unique_ptr<SelectToolTool>(new SelectToolTool(100, 100, *(SelectToolNode*)rootMenuNode.get()));

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

void SelectToolMenuManager::OpenMouseHighlightTool() noexcept{
    SetCurrTool(mouseHighlightTool.get());
}
