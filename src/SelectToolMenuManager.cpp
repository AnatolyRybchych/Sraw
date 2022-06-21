#include "SelectToolMenuManager.hpp"

SelectToolMenuManager::SelectToolMenuManager()
    :emptyTexture((GLuint)0){

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

