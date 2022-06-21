#include "SelectActionToolNode.hpp"

void SelectActionToolNode::OnSelect() noexcept{
    onSelecthandler();
}

const GLuint SelectActionToolNode::GetImage() const noexcept{
    return image.GetGLID();
}

const std::wstring &SelectActionToolNode::GetText() const noexcept{
    return text;
}

const std::vector<std::shared_ptr<SelectToolNode>> &SelectActionToolNode::GetToolNodes() const noexcept{
    return emptyNodesList;
}


SelectActionToolNode::SelectActionToolNode(Texture &image, std::wstring text, std::function<void()> onSelecthandler) noexcept
    :image(image), text(text), onSelecthandler(onSelecthandler){
}