#include "SelectMenuToolNode.hpp"
#include "Tools/SelectToolTool.hpp"

SelectMenuToolNode::SelectMenuToolNode(std::vector<SelectToolNode *> toolNodes, std::wstring text, const Texture &image, std::function<void(void)> onSelect) noexcept
    :toolNodes(toolNodes), text(text), image(image), onSelect(onSelect){
}

void SelectMenuToolNode::OnSelect() noexcept{if(onSelect) onSelect();}
const GLuint SelectMenuToolNode::GetImage() const noexcept{return image.GetGLID();}
const std::wstring &SelectMenuToolNode::GetText() const noexcept{ return text;}
const std::vector<SelectToolNode *> &SelectMenuToolNode::GetToolNodes() const noexcept{return toolNodes;}


