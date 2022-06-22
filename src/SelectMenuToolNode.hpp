#pragma once 
#include "SelectToolNode.hpp"

//should be parent to others nodes
class SelectMenuToolNode: SelectToolNode{
private:
    std::vector<SelectToolNode *> toolNodes;
    std::wstring text; 
    Texture &image;
protected:
    virtual void OnSelect() noexcept override;
    virtual const GLuint GetImage() const noexcept override;
    virtual const std::wstring &GetText() const noexcept override;
    virtual const std::vector<SelectToolNode *> &GetToolNodes() const noexcept override;
public:
    SelectMenuToolNode(std::vector<SelectToolNode *> toolNodes, std::wstring text, Texture &image) noexcept;
};


