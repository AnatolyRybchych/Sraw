#include "DrawingCanvas.hpp"
#include "ShaderDrawImage.hpp"
#include "ShaderProgram.hpp"

#include <iostream>

static GLuint TextureFromBitmap(HBITMAP hbmp);
static void fixBitmapData(void *data, int dataSize);

static void fixBitmapData(void *data, int dataSize){
    char *dataBeg = (char*)data;
    char *dataEnd = dataBeg + dataSize;

    for(char *ptr = dataBeg; ptr != dataEnd; ptr++){
        char tmp = ptr[0];
        ptr[0] = ptr[2];
        ptr[2] = tmp;
    }
}

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
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);

    DeleteDC(screenDc);
    DeleteDC(memDc);
    delete[] bmpData;

    return result;
}

DrawingCanvas::DrawingCanvas(int cx, int cy, HBITMAP bg)
    :cx(cx), cy(cy), bg(bg) {
    glViewport(0, 0, cx, cy);
    bgTexture = TextureFromBitmap(bg);
    drawImageProgram = BuildShaderProgram(DrawImageVertex, DrawImageFragment);
    drawImageVertexP = glGetAttribLocation(drawImageProgram, "vertex_p");
    drawImageTex = glGetUniformLocation(drawImageProgram, "tex");
}

DrawingCanvas::~DrawingCanvas() noexcept{
    glDeleteProgram(drawImageProgram);
    glDeleteTextures(1, &bgTexture);
}

void DrawingCanvas::DrawBG() const noexcept{
    static float vertices[] = {
        -1, 1, 1, -1, 1, 1,
        -1, 1, 1, -1, -1, -1
    };

    glUseProgram(drawImageProgram);
    glBindTexture(GL_TEXTURE_2D, bgTexture);
    
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(drawImageTex, 0);

    glEnableVertexAttribArray(drawImageVertexP);
    glVertexAttribPointer(drawImageVertexP, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/ sizeof(*vertices));
    glDisableVertexAttribArray(drawImageVertexP);

    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
}



void DrawingCanvas::Draw(){
    DrawBG();
}