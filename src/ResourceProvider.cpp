#include "UnicodeWindows.hpp"
#include "ResourceProvider.hpp"

#include <stb_image.h>
#include "paths.hpp"
#include "GlWrappers/ShaderProgram.hpp"
#include <fstream>

std::unique_ptr<ResourceProvider> ResourceProvider::provider;

static std::string FReadAllText(std::string path);
static GLuint ReadTexture(std::string path);

void ResourceProvider::InitProvider(){
    if(provider != nullptr) throw std::logic_error("provider is already initialized");
    provider = std::unique_ptr<ResourceProvider>(new ResourceProvider());
}

const ResourceProvider &ResourceProvider::GetProvider(){
    if(provider == nullptr) throw std::logic_error("provider is not initialized");
    return *provider;
}

ResourceProvider::ResourceProvider() noexcept
:mouseHighlightTexture(ReadTexture(FileMouseHighlightIcon)),
brushTexture(ReadTexture(FileBrushIcon)),
eraserTexture(ReadTexture(FileEraserIcon)),
colorPaletteTexture(ReadTexture(FileColorPaletteIcon)),
paletteTexture(ReadTexture(FilePalette)),
quitTexture(ReadTexture(FileQuiticon)),
clearTexture(ReadTexture(FileClearicon)),
hideTexture(ReadTexture(FileHideicon)),
saveToFileTexture(ReadTexture(FileSaveToFileicon)),
copyToClipboardTexture(ReadTexture(FileCopyToClipboardicon)),
toolsTexture(ReadTexture(FileToolsicon)),
textTexture(ReadTexture(FileTexticon)),
othersTexture(ReadTexture(FileOthersicon)),
primitivesTexture(ReadTexture(FilePrimitivesicon)),
blockDiagramTexture(ReadTexture(FileBlockDiagramicon)),
blockDiagramConditionTexture(ReadTexture(FileBlockDiagramConditionicon)),
blockDiagramStartEndTexture(ReadTexture(FileBlockDiagramStartEndicon)),
blockDiagramInOutTexture(ReadTexture(FileBlockDiagramInOuticon)),
blockDiagramFuncTexture(ReadTexture(FileBlockDiagramFuncicon)),
selectionTexture(ReadTexture(FileSelectionicon))
{
    menuBgProgram = BuildShaderProgram(FReadAllText(FileMenuBgVertex).c_str(), FReadAllText(FileMenuBgFragment).c_str());
    drawImageProgram = BuildShaderProgram(FReadAllText(FileDrawImageVertex).c_str(), FReadAllText(FileDrawImageFragment).c_str());
    menuItemProgram = BuildShaderProgram(FReadAllText(FileMenuItemVertex).c_str(), FReadAllText(FileMenuItemFragment).c_str());
    drawCircleProgram = BuildShaderProgram(FReadAllText(FileDrawCircleVertex).c_str(), FReadAllText(FileDrawCircleFragment).c_str());
    erseProgram = BuildShaderProgram(FReadAllText(FileErseVertex).c_str(), FReadAllText(FileErseFragment).c_str());
    paletteProgram = BuildShaderProgram(FReadAllText(FilePaletteVertex).c_str(), FReadAllText(FilePaletteFragment).c_str());
    mouseHighlightProgram = BuildShaderProgram(FReadAllText(FileMouseHighlightVertex).c_str(), FReadAllText(FileMouseHighlightFragment).c_str());
    drawActionDiagramBgProgram = BuildShaderProgram(FReadAllText(FileDrawActionDiagramBgVertex).c_str(), FReadAllText(FileDrawActionDiagramBgFragment).c_str());
    drawConditionDiagramBgProgram = BuildShaderProgram(FReadAllText(FileDrawConditionDiagramBgVertex).c_str(), FReadAllText(FileDrawConditionDiagramBgFragment).c_str());
    drawStartEndDiagramBgProgram = BuildShaderProgram(FReadAllText(FileDrawStartEndDiagramBgVertex).c_str(), FReadAllText(FileDrawStartEndDiagramBgFragment).c_str());
    drawInOutDiagramBgProgram = BuildShaderProgram(FReadAllText(FileDrawInOutDiagramBgVertex).c_str(), FReadAllText(FileDrawInOutDiagramBgFragment).c_str());
    drawFuncDiagramBgProgram = BuildShaderProgram(FReadAllText(FileDrawFuncDiagramBgVertex).c_str(), FReadAllText(FileDrawFuncDiagramBgFragment).c_str());
    fillRectProgram = BuildShaderProgram(FReadAllText(FileFillRectVertex).c_str(), FReadAllText(FileFillRectFragment).c_str());
}


static std::string FReadAllText(std::string path){
    std::ifstream file(path);
    if(file.is_open() == false) throw std::runtime_error(std::string("cannot open file \"") + path + "\"");

    std::string result((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return result;
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

const Texture &ResourceProvider::GetMouseHighlightTexture() const noexcept{
    return mouseHighlightTexture;
}

const Texture &ResourceProvider::GetBrushTexture() const noexcept{
    return brushTexture;
}

const Texture &ResourceProvider::GetEraserTexture() const noexcept{
    return eraserTexture;
}

const Texture &ResourceProvider::GetColorPaletteTexture() const noexcept{
    return colorPaletteTexture;
}

const Texture &ResourceProvider::GetPaletteTexture() const noexcept{
    return paletteTexture;
}

const Texture &ResourceProvider::GetQuitTexture() const noexcept{
    return quitTexture;
}

const Texture &ResourceProvider::GetClearTexture() const noexcept{
    return clearTexture;
}

const Texture &ResourceProvider::GetHideTexture() const noexcept{
    return hideTexture;
}

const Texture &ResourceProvider::GetSaveToFileTexture() const noexcept{
    return saveToFileTexture;
}

const Texture &ResourceProvider::GetCopyToClipboardTexture() const noexcept{
    return copyToClipboardTexture;
}

const Texture &ResourceProvider::GetToolsTexture() const noexcept{
    return toolsTexture;
}

const Texture &ResourceProvider::GetTextTexture() const noexcept{
    return textTexture;
}

const Texture &ResourceProvider::GetOthersTexture() const noexcept{
    return othersTexture;
}

const Texture &ResourceProvider::GetPrimitivesTexture() const noexcept{
    return primitivesTexture;
}

const Texture &ResourceProvider::GetBlockDiagramTexture() const noexcept{
    return blockDiagramTexture;
}

const Texture &ResourceProvider::GetBlockDiagramConditionTexture() const noexcept{
    return blockDiagramConditionTexture;
}

const Texture &ResourceProvider::GetBlockDiagramStartEndTexture() const noexcept{
    return blockDiagramStartEndTexture;
}

const Texture &ResourceProvider::GetBlockDiagramInOutTexture() const noexcept{
    return blockDiagramInOutTexture;
}

const Texture &ResourceProvider::GetBlockDiagramFuncTexture() const noexcept{
    return blockDiagramFuncTexture;
}

const Texture &ResourceProvider::GetSelectionTexture() const noexcept{
    return selectionTexture;
}
    
GLuint ResourceProvider::GetMenuBgProgram() const noexcept{
    return menuBgProgram;
}

GLuint ResourceProvider::GetDrawImageProgram() const noexcept{
    return drawImageProgram;
}

GLuint ResourceProvider::GetMenuItemProgram() const noexcept{
    return menuItemProgram;
}

GLuint ResourceProvider::GetDrawCircleProgram() const noexcept{
    return drawCircleProgram;
}

GLuint ResourceProvider::GetErseProgram() const noexcept{
    return erseProgram;
}

GLuint ResourceProvider::GetPaletteProgram() const noexcept{
    return paletteProgram;
}

GLuint ResourceProvider::GetMouseHighlightProgram() const noexcept{
    return mouseHighlightProgram;
}

GLuint ResourceProvider::GetDrawActionDiagramBgProgram() const noexcept{
    return drawActionDiagramBgProgram;
}

GLuint ResourceProvider::GetDrawConditionDiagramBgProgram() const noexcept{
    return drawConditionDiagramBgProgram;
}

GLuint ResourceProvider::GetDrawStartEndDiagramBgProgram() const noexcept{
    return drawStartEndDiagramBgProgram;
}

GLuint ResourceProvider::GetDrawInOutDiagramBgProgram() const noexcept{
    return drawInOutDiagramBgProgram;
}

GLuint ResourceProvider::GetDrawFuncDiagramBgProgram() const noexcept{
    return drawFuncDiagramBgProgram;
}

GLuint ResourceProvider::GetFillRectProgram() const noexcept{
    return fillRectProgram;
}

