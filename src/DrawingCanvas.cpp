#include "DrawingCanvas.hpp"
#include "ShaderDrawImage.hpp"
#include "ShaderProgram.hpp"

#include <iostream>



static void fixBitmapData(void *data, int dataSize);

static float vertices[] = {
    -1, 1, 1, -1, 1, 1,
    -1, 1, 1, -1, -1, -1
};

static void fixBitmapData(void *data, int dataSize){
    char *dataBeg = (char*)data;
    char *dataEnd = dataBeg + dataSize;

    for(char *ptr = dataBeg; ptr != dataEnd; ptr++){
        char tmp = ptr[0];
        ptr[0] = ptr[2];
        ptr[2] = tmp;
    }
}

const Texture &DrawingCanvas::GetBackground() const noexcept{
    return bg;
}

DrawingCanvas::DrawingCanvas(Texture &bg)
    :bg(bg) {
    drawImageProgram = BuildShaderProgram(DrawImageVertex, DrawImageFragment);
    drawImageVertexP = glGetAttribLocation(drawImageProgram, "vertex_p");
    drawImageTex = glGetUniformLocation(drawImageProgram, "tex");
}

DrawingCanvas::~DrawingCanvas() noexcept{
    glDeleteProgram(drawImageProgram);
}

void DrawingCanvas::Draw(){
    glUseProgram(drawImageProgram);
    glBindTexture(GL_TEXTURE_2D, currState->GetGLID());
    
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(drawImageTex, 0);

    glEnableVertexAttribArray(drawImageVertexP);
    glVertexAttribPointer(drawImageVertexP, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/ sizeof(*vertices));
    glDisableVertexAttribArray(drawImageVertexP);

    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
}

void DrawingCanvas::OnShow(int cx, int cy){
    this->cx = cx;
    this->cy = cy;

    currState = std::unique_ptr<Texture>(new Texture(cx, cy));

    frameBuffer.Bind();
    glViewport(0, 0, cx, cy);
    frameBuffer.AttachTexture2D(currState->GetGLID());

    glUseProgram(drawImageProgram);
    glBindTexture(GL_TEXTURE_2D, bg.GetGLID());
    
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(drawImageTex, 0);

    glEnableVertexAttribArray(drawImageVertexP);
    glVertexAttribPointer(drawImageVertexP, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/ sizeof(*vertices));
    glDisableVertexAttribArray(drawImageVertexP);

    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);

    frameBuffer.Unbind();
    glViewport(0, 0, cx, cy);   
}