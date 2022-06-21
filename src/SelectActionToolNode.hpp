#pragma once
#include "SelectToolNode.hpp"

class SelectActionToolNode: public SelectToolNode{
private:
    Texture &image;
    std::wstring text;
    std::function<void()> onSelecthandler;
    std::vector<std::shared_ptr<SelectToolNode>> emptyNodesList;
protected:
    virtual void OnSelect() noexcept override;
    virtual const GLuint GetImage() const noexcept override;
    virtual const std::wstring &GetText() const noexcept override;
    virtual const std::vector<std::shared_ptr<SelectToolNode>> &GetToolNodes() const noexcept override;
public:
    SelectActionToolNode(Texture &image, std::wstring text, std::function<void()> onSelecthandler) noexcept;
};

