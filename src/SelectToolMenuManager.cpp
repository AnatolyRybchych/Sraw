#include "SelectToolMenuManager.hpp"
#include "MouseHighlightTool.hpp"

SelectToolMenuManager::SelectToolMenuManager()
    :emptyTexture((GLuint)0){
        
    currTool = std::unique_ptr<DrawingTool>(new MouseHighlightTool(100, 100));

    rootMenuNode = std::unique_ptr<SelectMenuToolNode>(
        new SelectMenuToolNode(
        std::vector<std::shared_ptr<SelectToolNode>>{

        }, 
        L"root", 
        emptyTexture)
    );
}

SelectToolTool *SelectToolMenuManager::CreateSelectToolMenu(int cx, int cy){
    return new SelectToolTool(cx, cy, *(SelectToolNode*)rootMenuNode.get());
}

DrawingTool &SelectToolMenuManager::GetCurrTool() noexcept{
    return *currTool.get();
}

void SelectToolMenuManager::OpenToolMenu() noexcept{
    currTool = std::unique_ptr<DrawingTool>(CreateSelectToolMenu(currTool->GetViewportWidth(), currTool->GetViewportHeight()));
}
