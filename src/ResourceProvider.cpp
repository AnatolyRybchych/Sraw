#include "UnicodeWindows.hpp"
#include "ResourceProvider.hpp"

#include <stb_image.h>
#include "paths.hpp"

#include <fstream>

std::unique_ptr<ResourceProvider> ResourceProvider::provider;

static std::string FReadAllText(std::string path);
static GLuint ReadTexture(std::string path);

const ResourceProvider &ResourceProvider::GetProvider() noexcept{
    if(provider == nullptr) provider = std::unique_ptr<ResourceProvider>(new ResourceProvider());

    return *provider;
}

ResourceProvider::ResourceProvider() noexcept{

}

GLuint ResourceProvider::GetMouseHighlightIcon() const noexcept{
    return ReadTexture(FileMouseHighlightIcon);
}

GLuint ResourceProvider::GetBrushIcon() const noexcept{
    return ReadTexture(FileBrushIcon);
}

GLuint ResourceProvider::GetEraserIcon() const noexcept{
    return ReadTexture(FileEraserIcon);
}

GLuint ResourceProvider::GetColorPaletteIcon() const noexcept{
    return ReadTexture(FileColorPaletteIcon); 
}

GLuint ResourceProvider::GetPalette() const noexcept{
    return ReadTexture(FilePalette); 
}

GLuint ResourceProvider::GetQuitIcon() const noexcept{
    return ReadTexture(FileQuiticon); 
}

std::string ResourceProvider::GetMenuBgFragment() const noexcept{
    return FReadAllText(FileMenuBgFragment);
}

std::string ResourceProvider::GetMenuBgVertex() const noexcept{
    return FReadAllText(FileMenuBgVertex);
}

std::string ResourceProvider::GetDrawImageVertex() const noexcept{
    return FReadAllText(FileDrawImageVertex);
}

std::string ResourceProvider::GetDrawImageFragment() const noexcept{
    return FReadAllText(FileDrawImageFragment);
}

std::string ResourceProvider::GetMenuItemFragment() const noexcept{
    return FReadAllText(FileMenuItemFragment);
}

std::string ResourceProvider::GetMenuItemVertex() const noexcept{
    return FReadAllText(FileMenuItemVertex);
}

std::string ResourceProvider::GetDrawCircleVertex() const noexcept{
    return FReadAllText(FileDrawCircleVertex);
}

std::string ResourceProvider::GetDrawCircleFragment() const noexcept{
    return FReadAllText(FileDrawCircleFragment);
}

std::string ResourceProvider::GetErseVertex() const noexcept{
    return FReadAllText(FileErseVertex);
}

std::string ResourceProvider::GetErseFragment() const noexcept{
    return FReadAllText(FileErseFragment);
}

std::string ResourceProvider::GetPaletteVertex() const noexcept{
    return FReadAllText(FilePaletteVertex);
}

std::string ResourceProvider::GetPaletteFragment() const noexcept{
    return FReadAllText(FilePaletteFragment);
}

static std::string FReadAllText(std::string path){
    std::ifstream file(path);
    if(file.is_open() == false) throw std::runtime_error(std::string("cannot open file \"") + path + "\"");

    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

static GLuint ReadTexture(std::string path){
    int cx, cy, cnt;
    unsigned char *data = stbi_load(path.c_str(), &cx, &cy, &cnt, 0);

    if(data == nullptr) MessageBoxA(NULL, (std::string() + "Cannot find file \"" + path + "\"").c_str(), "ERROR" , MB_OK);

    GLuint result;
    glGenTextures(1, &result);
    glBindTexture(GL_TEXTURE_2D, result);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cx, cy, 0, cnt == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);

    return result;
}
