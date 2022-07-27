#pragma once
#include <memory>
#include <string>
#include <GL/glew.h>

class ResourceProvider{
private:
    static std::unique_ptr<ResourceProvider> provider;
    ResourceProvider() noexcept;
public:
    static const ResourceProvider &GetProvider() noexcept;

    GLuint GetMouseHighlightIcon() const noexcept;
    GLuint GetBrushIcon() const noexcept;
    GLuint GetEraserIcon() const noexcept;
    GLuint GetColorPaletteIcon() const noexcept;
    GLuint GetPalette() const noexcept;
    GLuint GetQuitIcon() const noexcept;
    GLuint GetClearIcon() const noexcept;
    GLuint GetHideIcon() const noexcept;
    GLuint GetSaveToFileIcon() const noexcept;
    GLuint GetCopyToClipboardIcon() const noexcept;
    GLuint GetToolsIcon() const noexcept;
    
    std::string GetMenuBgFragment() const noexcept;
    std::string GetMenuBgVertex() const noexcept;
    std::string GetDrawImageVertex() const noexcept;
    std::string GetDrawImageFragment() const noexcept;
    std::string GetMenuItemFragment() const noexcept;
    std::string GetMenuItemVertex() const noexcept;
    std::string GetDrawCircleVertex() const noexcept;
    std::string GetDrawCircleFragment() const noexcept;
    std::string GetErseVertex() const noexcept;
    std::string GetErseFragment() const noexcept;
    std::string GetPaletteVertex() const noexcept;
    std::string GetPaletteFragment() const noexcept;
};
