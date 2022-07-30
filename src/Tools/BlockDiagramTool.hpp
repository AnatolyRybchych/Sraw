#include "../DrawingTool.hpp"
#include "../GlWrappers/RenderText.hpp"
#include "ColorPaletTool.hpp"


class BlockDiagramSetting{
private:
    float fontSize;
    ColorPaletTool &paletTool;
public:
    BlockDiagramSetting(ColorPaletTool &paletTool,int fontSize) noexcept;
    const ColorPaletTool &GetPalet() const noexcept;
    ColorPaletTool &GetPaletRef() noexcept;
    void FontSizeInc() noexcept;
    void FontSizeDec() noexcept;
    int GetFontSize() const noexcept;
};

class BlockDiagramTool:public DrawingTool{
private:
    std::wstring text;
    BlockDiagramSetting &settings;

    bool isMouseDown = false;
    bool isControlDown = false;

    int currX;
    int currY;
protected://handlers should return true if requires to redraw
    virtual void OnDraw() const noexcept override;
    virtual bool OnMouseMove(int x, int y) noexcept override; 
    virtual bool OnLMouseDown(int x, int y) noexcept override;
    virtual bool OnLMouseUp(int x, int y) noexcept override;
    virtual bool OnKeyDown(int vkCode, int repeat) noexcept override;
    virtual bool OnKeyUp(int vkCode) noexcept override;
    virtual bool OnTextInput(std::wstring str) noexcept override;
    virtual bool OnScrollUp() noexcept override;
    virtual bool OnScrollDown() noexcept override;
    virtual void DrawBg() const noexcept = 0;
    virtual void DrawTxt() const noexcept = 0;
public:
    BlockDiagramTool(int cx, int cy, CommitHandler &commitHandler, const Texture &bg, BlockDiagramSetting &settings);

    int GetCurrMPosX() const noexcept;
    int GetCurrMPosY() const noexcept;

    const BlockDiagramSetting &GetSettings() const noexcept;
    BlockDiagramSetting &GetSettingsRef() noexcept;
    std::wstring GetText() const noexcept;
    void SetText(std::wstring text) noexcept;
    virtual int GetTextWidth() const noexcept = 0;
};