#include "Texture.hpp"

static GLuint TextureFromBitmap(HBITMAP hbmp);

static GLuint TextureFromBitmap(HBITMAP hbmp){
    HDC screenDc = GetDC(NULL);
    HDC memDc = CreateCompatibleDC(screenDc);

    SelectObject(memDc, hbmp);
    BITMAPINFO info;
    memset(&info, 0, sizeof(info));
    info.bmiHeader.biSize = sizeof(info.bmiHeader);
    GetDIBits(memDc, hbmp, 0, 0, NULL, &info, DIB_RGB_COLORS);
    info.bmiHeader.biCompression = BI_RGB;
    int dataLen = (info.bmiHeader.biBitCount * info.bmiHeader.biWidth * info.bmiHeader.biHeight + 7) / 8;
    char *bmpData = new char[dataLen];
    GetDIBits(memDc, hbmp, 0, info.bmiHeader.biHeight, bmpData, &info, DIB_RGB_COLORS);

    GLuint result;
    glGenTextures(1, &result);
    glBindTexture(GL_TEXTURE_2D, result);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, info.bmiHeader.biWidth, info.bmiHeader.biHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, bmpData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);

    DeleteDC(screenDc);
    DeleteDC(memDc);
    delete[] bmpData;

    return result;
}

Texture::Texture(HBITMAP hbmp){
    glId = TextureFromBitmap(hbmp);
}

Texture::Texture(int cx, int cy){
    GLuint result;

    glGenTextures(1, &result);
    glBindTexture(GL_TEXTURE_2D, result);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cx, cy, 0, GL_BGRA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);

    glId = result;
}

GLuint Texture::GetGLID() const noexcept{
    return glId;
}


Texture::~Texture(){
    glDeleteTextures(1, &glId);
}