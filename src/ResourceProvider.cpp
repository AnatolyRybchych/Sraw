#include "UnicodeWindows.hpp"
#include "ResourceProvider.hpp"

#include <stdio.h>
#include <stb_image.h>
#include "paths.hpp"
#include "GlWrappers/ShaderProgram.hpp"
#include <fstream>

std::unique_ptr<ResourceProvider> ResourceProvider::provider;

static std::string FReadAllText(std::wstring path);
static std::wstring AbsolutePath(std::wstring rel) noexcept;
static std::wstring AbsolutePath(std::string rel) noexcept;
static GLuint ReadTexture(std::wstring path);

void ResourceProvider::InitProvider(){
    if(provider != nullptr) throw std::logic_error("provider is already initialized");
    provider = std::unique_ptr<ResourceProvider>(new ResourceProvider());
}

const ResourceProvider &ResourceProvider::GetProvider(){
    if(provider == nullptr) throw std::logic_error("provider is not initialized");
    return *provider;
}

ResourceProvider::ResourceProvider() noexcept
:mouseHighlightTexture(ReadTexture(AbsolutePath(FileMouseHighlightIcon))),
brushTexture(ReadTexture(AbsolutePath(FileBrushIcon))),
eraserTexture(ReadTexture(AbsolutePath(FileEraserIcon))),
colorPaletteTexture(ReadTexture(AbsolutePath(FileColorPaletteIcon))),
paletteTexture(ReadTexture(AbsolutePath(FilePalette))),
quitTexture(ReadTexture(AbsolutePath(FileQuiticon))),
clearTexture(ReadTexture(AbsolutePath(FileClearicon))),
hideTexture(ReadTexture(AbsolutePath(FileHideicon))),
saveToFileTexture(ReadTexture(AbsolutePath(FileSaveToFileicon))),
copyToClipboardTexture(ReadTexture(AbsolutePath(FileCopyToClipboardicon))),
toolsTexture(ReadTexture(AbsolutePath(FileToolsicon))),
textTexture(ReadTexture(AbsolutePath(FileTexticon))),
othersTexture(ReadTexture(AbsolutePath(FileOthersicon))),
primitivesTexture(ReadTexture(AbsolutePath(FilePrimitivesicon))),
blockDiagramTexture(ReadTexture(AbsolutePath(FileBlockDiagramicon))),
blockDiagramConditionTexture(ReadTexture(AbsolutePath(FileBlockDiagramConditionicon))),
blockDiagramStartEndTexture(ReadTexture(AbsolutePath(FileBlockDiagramStartEndicon))),
blockDiagramInOutTexture(ReadTexture(AbsolutePath(FileBlockDiagramInOuticon))),
blockDiagramFuncTexture(ReadTexture(AbsolutePath(FileBlockDiagramFuncicon))),
selectionTexture(ReadTexture(AbsolutePath(FileSelectionicon))),
circleTexture(ReadTexture(AbsolutePath(FileCircleicon))),
graphTexture(ReadTexture(AbsolutePath(FileGraphicon))),
lineTexture(ReadTexture(AbsolutePath(FileLineicon))),
rectTexture(ReadTexture(AbsolutePath(FileRecticon))),
rectOutlineTexture(ReadTexture(AbsolutePath(FileRectOutlineicon)))
{
    menuBgProgram = BuildShaderProgram(FReadAllText(AbsolutePath(FileMenuBgVertex)).c_str(), FReadAllText(AbsolutePath(FileMenuBgFragment)).c_str());
    drawImageProgram = BuildShaderProgram(FReadAllText(AbsolutePath(FileDrawImageVertex)).c_str(), FReadAllText(AbsolutePath(FileDrawImageFragment)).c_str());
    menuItemProgram = BuildShaderProgram(FReadAllText(AbsolutePath(FileMenuItemVertex)).c_str(), FReadAllText(AbsolutePath(FileMenuItemFragment)).c_str());
    drawCircleProgram = BuildShaderProgram(FReadAllText(AbsolutePath(FileDrawCircleVertex)).c_str(), FReadAllText(AbsolutePath(FileDrawCircleFragment)).c_str());
    paletteProgram = BuildShaderProgram(FReadAllText(AbsolutePath(FilePaletteVertex)).c_str(), FReadAllText(AbsolutePath(FilePaletteFragment)).c_str());
    mouseHighlightProgram = BuildShaderProgram(FReadAllText(AbsolutePath(FileMouseHighlightVertex)).c_str(), FReadAllText(AbsolutePath(FileMouseHighlightFragment)).c_str());
    drawActionDiagramBgProgram = BuildShaderProgram(FReadAllText(AbsolutePath(FileDrawActionDiagramBgVertex)).c_str(), FReadAllText(AbsolutePath(FileDrawActionDiagramBgFragment)).c_str());
    drawConditionDiagramBgProgram = BuildShaderProgram(FReadAllText(AbsolutePath(FileDrawConditionDiagramBgVertex)).c_str(), FReadAllText(AbsolutePath(FileDrawConditionDiagramBgFragment)).c_str());
    drawStartEndDiagramBgProgram = BuildShaderProgram(FReadAllText(AbsolutePath(FileDrawStartEndDiagramBgVertex)).c_str(), FReadAllText(AbsolutePath(FileDrawStartEndDiagramBgFragment)).c_str());
    drawInOutDiagramBgProgram = BuildShaderProgram(FReadAllText(AbsolutePath(FileDrawInOutDiagramBgVertex)).c_str(), FReadAllText(AbsolutePath(FileDrawInOutDiagramBgFragment)).c_str());
    drawFuncDiagramBgProgram = BuildShaderProgram(FReadAllText(AbsolutePath(FileDrawFuncDiagramBgVertex)).c_str(), FReadAllText(AbsolutePath(FileDrawFuncDiagramBgFragment)).c_str());
    fillRectProgram = BuildShaderProgram(FReadAllText(AbsolutePath(FileFillRectVertex)).c_str(), FReadAllText(AbsolutePath(FileFillRectFragment)).c_str());
    renderTextProgram = BuildShaderProgram(FReadAllText(AbsolutePath(FileRenderTextVertex)).c_str(), FReadAllText(AbsolutePath(FileRenderTextFragment)).c_str());
}


static std::string FReadAllText(std::wstring path){
    std::wifstream file(path.c_str());
    if(file.is_open() == false) throw std::runtime_error(std::string("cannot open file \"") + std::string(path.begin(), path.end()) + "\"");
    
    std::wstring result((std::istreambuf_iterator<wchar_t>(file)), std::istreambuf_iterator<wchar_t>());
    file.close();
    return std::string(result.begin(), result.end());
}

static GLuint ReadTexture(std::wstring path){
    int cx, cy, cnt;
    FILE *file = _wfopen(path.c_str(), L"rb");
    unsigned char *data = stbi_load_from_file(file, &cx, &cy, &cnt, 0);

    if(data == nullptr) MessageBoxA(NULL, (std::string() + "Cannot find file \"" + std::string(path.begin(), path.end()) + "\"").c_str(), "ERROR" , MB_OK);

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

const Texture &ResourceProvider::GetCircleTexture() const noexcept{
    return circleTexture;
}

const Texture &ResourceProvider::GetGraphTexture() const noexcept{
    return graphTexture;
}

const Texture &ResourceProvider::GetLineTexture() const noexcept{
    return lineTexture;
}

const Texture &ResourceProvider::GetRectTexture() const noexcept{
    return rectTexture;
}

const Texture &ResourceProvider::GetRectOutlineTexture() const noexcept{
    return rectOutlineTexture;
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

GLuint ResourceProvider::GetRenderTextProgram() const noexcept{
    return renderTextProgram;
}

static std::wstring AbsolutePath(std::string rel) noexcept{
    return AbsolutePath(std::wstring(rel.begin(), rel.end()));
}

static std::wstring AbsolutePath(std::wstring rel) noexcept{
    static wchar_t fullFilename[MAX_PATH];

    if(GetFullPathNameW(rel.c_str(), MAX_PATH, fullFilename, nullptr)){
        return fullFilename;
    }
    else{
        return L"";
    }
}

