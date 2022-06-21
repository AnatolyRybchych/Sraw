#include "SelectMenuToolNode.hpp"
#include "SelectToolTool.hpp"

SelectMenuToolNode::SelectMenuToolNode(std::vector<std::shared_ptr<SelectToolNode>> toolNodes, std::wstring text, Texture &image) noexcept
    :toolNodes(toolNodes), text(text), image(image){
}

void SelectMenuToolNode::OnSelect() noexcept{}
const GLuint SelectMenuToolNode::GetImage() const noexcept{return image.GetGLID();}
const std::wstring &SelectMenuToolNode::GetText() const noexcept{ return text;}
const std::vector<std::shared_ptr<SelectToolNode>> &SelectMenuToolNode::GetToolNodes() const noexcept{return toolNodes;}


