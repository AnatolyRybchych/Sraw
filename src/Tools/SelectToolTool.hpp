#pragma once 
#include "../DrawingTool.hpp"
#include "SelectToolNode.hpp"

class SelectToolTool: public DrawingTool{
private:
    SelectToolNode &rootNode;
    SelectToolNode *currNode = nullptr;
    int nodeOver = -1;
protected:
    virtual void OnDraw() const noexcept override;
    virtual bool OnMouseMove(int x, int y) noexcept override; 
    virtual bool OnLMouseDown(int x, int y) noexcept override;
    virtual bool OnLMouseUp(int x, int y) noexcept override;
    virtual bool OnKeyDown(int vkCode, int repeat) noexcept override;
    virtual bool OnKeyUp(int vkCode) noexcept override;
    virtual bool OnTextInput(std::wstring str) noexcept override;
    virtual bool OnScrollUp() noexcept override;
    virtual bool OnScrollDown() noexcept override;
public:
    void SetCurrNode(SelectToolNode *node) noexcept;
    SelectToolTool(int cx, int cy, CommitHandler &commitHandler, const Texture &bg, SelectToolNode &rootToolNode) noexcept;
};