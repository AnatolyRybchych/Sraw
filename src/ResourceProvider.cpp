#include "UnicodeWindows.hpp"
#include "ResourceProvider.hpp"

#include <stb_image.h>
#include "paths.hpp"

#include <fstream>

std::unique_ptr<ResourceProvider> ResourceProvider::provider;

static std::string FReadAllText(std::string path);

const ResourceProvider &ResourceProvider::GetProvider() noexcept{
    if(provider == nullptr) provider = std::unique_ptr<ResourceProvider>(new ResourceProvider());

    return *provider;
}

ResourceProvider::ResourceProvider() noexcept{

}

GLuint ResourceProvider::GetMouseHighlightIcon() const noexcept{
    int cx, cy, cnt;
    unsigned char *data = stbi_load(FileMouseHighlightIcon, &cx, &cy, &cnt, 0);

    if(data == nullptr) MessageBoxA(NULL, (std::string() + "Cannot find file \"" + FileMouseHighlightIcon + "\"").c_str(), "ERROR" , MB_OK);

    GLuint result;
    glGenTextures(1, &result);
    glBindTexture(GL_TEXTURE_2D, result);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cx, cy, 0, cnt == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);

    return result;
}

std::string ResourceProvider::GetMenuBgFragment() const noexcept{
    return FReadAllText(FileMenuBgFragment);
}

std::string ResourceProvider::GetMenuBgVertex() const noexcept{
    return FReadAllText(FileMenuBgVertex);
}

std::string ResourceProvider::GetMenuItemFragment() const noexcept{
    return FReadAllText(FileMenuItemFragment);
}

std::string ResourceProvider::GetMenuItemVertex() const noexcept{
    return FReadAllText(FileMenuItemVertex);
}

static std::string FReadAllText(std::string path){
    std::ifstream file(path);
    if(file.is_open() == false) throw std::runtime_error(std::string("cannot open file \"") + path + "\"");

    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}
