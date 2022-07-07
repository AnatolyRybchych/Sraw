#pragma once
#include <memory>
#include <string>
#include <glad/glad.h>

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
};
