#pragma once
#include "SelectToolNode.hpp"

class SelectActionToolNode: public SelectToolNode{
private:
    const Texture &image;
    std::wstring text;
    std::function<void()> onSelecthandler;
    std::vector<SelectToolNode *> emptyNodesList;
protected:
    virtual void OnSelect() noexcept override;
    virtual const GLuint GetImage() const noexcept override;
    virtual const std::wstring &GetText() const noexcept override;
    virtual const std::vector<SelectToolNode *> &GetToolNodes() const noexcept override;
public:
    SelectActionToolNode(const Texture &image, std::wstring text, std::function<void()> onSelecthandler) noexcept;
};

