#pragma once
#include <memory>
#include <string>
#include <GL/glew.h>
#include "GlWrappers/Texture.hpp"

class ResourceProvider{
private:
    static std::unique_ptr<ResourceProvider> provider;
    ResourceProvider() noexcept;

    Texture mouseHighlightTexture;
    Texture brushTexture;
    Texture eraserTexture;
    Texture colorPaletteTexture;
    Texture paletteTexture;
    Texture quitTexture;
    Texture clearTexture;
    Texture hideTexture;
    Texture saveToFileTexture;
    Texture copyToClipboardTexture;
    Texture toolsTexture;
    Texture textTexture;
    Texture othersTexture;
    Texture primitivesTexture;
    Texture blockDiagramTexture;
    Texture blockDiagramConditionTexture;
    Texture blockDiagramStartEndTexture;
    Texture blockDiagramInOutTexture;
    Texture blockDiagramFuncTexture;
    Texture selectionTexture;

    GLuint menuBgProgram;
    GLuint drawImageProgram;
    GLuint menuItemProgram;
    GLuint drawCircleProgram;
    GLuint erseProgram;
    GLuint paletteProgram;
    GLuint mouseHighlightProgram;
    GLuint drawActionDiagramBgProgram;
    GLuint drawConditionDiagramBgProgram;
    GLuint drawStartEndDiagramBgProgram;
    GLuint drawInOutDiagramBgProgram;
    GLuint drawFuncDiagramBgProgram;
    GLuint fillRectProgram;
public:
    static void InitProvider();
    static const ResourceProvider &GetProvider();

    const Texture &GetMouseHighlightTexture() const noexcept;
    const Texture &GetBrushTexture() const noexcept;
    const Texture &GetEraserTexture() const noexcept;
    const Texture &GetColorPaletteTexture() const noexcept;
    const Texture &GetPaletteTexture() const noexcept;
    const Texture &GetQuitTexture() const noexcept;
    const Texture &GetClearTexture() const noexcept;
    const Texture &GetHideTexture() const noexcept;
    const Texture &GetSaveToFileTexture() const noexcept;
    const Texture &GetCopyToClipboardTexture() const noexcept;
    const Texture &GetToolsTexture() const noexcept;
    const Texture &GetTextTexture() const noexcept;
    const Texture &GetOthersTexture() const noexcept;
    const Texture &GetPrimitivesTexture() const noexcept;
    const Texture &GetBlockDiagramTexture() const noexcept;
    const Texture &GetBlockDiagramConditionTexture() const noexcept;
    const Texture &GetBlockDiagramStartEndTexture() const noexcept;
    const Texture &GetBlockDiagramInOutTexture() const noexcept;
    const Texture &GetBlockDiagramFuncTexture() const noexcept;
    const Texture &GetSelectionTexture() const noexcept;
        
    GLuint GetMenuBgProgram() const noexcept;
    GLuint GetDrawImageProgram() const noexcept;
    GLuint GetMenuItemProgram() const noexcept;
    GLuint GetDrawCircleProgram() const noexcept;
    GLuint GetErseProgram() const noexcept;
    GLuint GetPaletteProgram() const noexcept;
    GLuint GetMouseHighlightProgram() const noexcept;
    GLuint GetDrawActionDiagramBgProgram() const noexcept;
    GLuint GetDrawConditionDiagramBgProgram() const noexcept;
    GLuint GetDrawStartEndDiagramBgProgram() const noexcept;
    GLuint GetDrawInOutDiagramBgProgram() const noexcept;
    GLuint GetDrawFuncDiagramBgProgram() const noexcept;
    GLuint GetFillRectProgram() const noexcept;
    
};
