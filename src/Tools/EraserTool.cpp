#include "../ResourceProvider.hpp"
#include "EraserTool.hpp"
#include "../GlWrappers/ShaderProgram.hpp"
#include "../DrawImage.hpp"
#include <math.h>

static int distancei(int x1, int y1, int x2, int y2){
    int x = x2 - x1;
    int y = y2 - y1;
    return (int)(sqrt(x*x + y*y) + 0.5);
}

void EraserTool::Erse(int x, int y) const noexcept{
    glUseProgram(prog);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(vertex_pPos);
    glBindTexture(GL_TEXTURE_2D, bg);
    glActiveTexture(GL_TEXTURE0);
    
    glUniform2f(posPos, (x / (float)GetViewportWidth() - 0.5) * 2.0, (0.5 - y / (float)GetViewportHeight()) * 2.0);
    glUniform2f(viewportPos, (float)GetViewportWidth(),(float)GetViewportHeight());
    glUniform1i(bgPos, 0);
    glUniform1f(scalePos, scale);

    glVertexAttribPointer(vertex_pPos, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisableVertexAttribArray(vertex_pPos);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}

void EraserTool::ClearBuffer() const noexcept{
    frameBuffer->Bind();
    frameBuffer->AttachTexture2D(buffer->GetGLID());
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    frameBuffer->Unbind();
}

void EraserTool::OnDraw() const noexcept{
    DrawImage::GetRenderer().Draw(buffer->GetGLID());
    Erse(prevX, prevY);
}

void EraserTool::OnDrawCommit() noexcept{
    DrawImage::GetRenderer().Draw(buffer->GetGLID());
}

void EraserTool::OnResize(int cx, int cy) noexcept{
    Texture *newBuffer = new Texture(cx, cy);
    frameBuffer->AttachTexture2D(newBuffer->GetGLID());
    frameBuffer->Bind();
    DrawImage::GetRenderer().Draw(buffer->GetGLID());
    frameBuffer->Unbind();

    buffer = std::unique_ptr<Texture>(newBuffer);
}

bool EraserTool::OnMouseMove(int x, int y) noexcept{
    if(isMouseDown){
        frameBuffer->Bind();
        frameBuffer->AttachTexture2D(buffer->GetGLID());

        int points = distancei(prevX, prevY, x, y);
        int distanceX = x - prevX;
        int distanceY = y - prevY;
        for(int i = 0; i <= points; i++){
            Erse(
                prevX + (i / (float)points) * (float)distanceX,
                prevY + (i / (float)points) * (float)distanceY
            );
        }

        frameBuffer->Unbind();
        prevX = x;
        prevY = y;
        return true;
    }
    prevX = x;
    prevY = y;
    return true;
} 

bool EraserTool::OnLMouseDown(int x, int y) noexcept{
    isMouseDown = true;
    prevX = x;
    prevY = y;
    OnMouseMove(x + 1, y);
    return true;
}

bool EraserTool::OnLMouseUp(int x, int y) noexcept{
    if(isMouseDown){
        OnMouseMove(x, y);
        isMouseDown = false;

        Commit();
        ClearBuffer();
        prevX = x;
        prevY = y;
        return true;
    }
    prevX = x;
    prevY = y;
    return true;
}

bool EraserTool::OnKeyDown(int vkCode, int repeat) noexcept{
    switch (vkCode)
    {
    case VK_OEM_6:{
        scale *= 1.0 + scaleIncrement;
        if(scale > scaleMax) scale = scaleMax;
    } return true;
    case VK_OEM_4:{
        scale *= 1.0 - scaleIncrement;
        if(scale < scaleMin) scale = scaleMin;  
    } return true;
    default: return false;
    }
}

bool EraserTool::OnKeyUp(int vkCode) noexcept{
    return false;
}

bool EraserTool::OnTextInput(std::wstring str) noexcept{
    return false;
}

bool EraserTool::OnScrollUp() noexcept{
    scale *= 1.0 + scaleIncrement;
        if(scale > scaleMax) scale = scaleMax;
    return true;
}

bool EraserTool::OnScrollDown() noexcept{
    scale *= 1.0 - scaleIncrement;
        if(scale < scaleMin) scale = scaleMin;  
    return true;
}


EraserTool::EraserTool(int cx, int cy, CommitHandler &commitHandler, GLuint bg) noexcept
    :DrawingTool(cx, cy, commitHandler),
    buffer(new Texture(cx, cy)),
    frameBuffer(new Framebuffer()),
    bg(bg){

    ClearBuffer();

    prog = BuildShaderProgram(
        ResourceProvider::GetProvider().GetErseVertex().c_str(),
        ResourceProvider::GetProvider().GetErseFragment().c_str()
    );

    vertex_pPos = glGetAttribLocation(prog, "vertex_p");
    posPos = glGetUniformLocation(prog, "pos");
    viewportPos = glGetUniformLocation(prog, "viewport");
    scalePos = glGetUniformLocation(prog, "scale");
    bgPos = glGetUniformLocation(prog, "bg");

    
    float vertices[] = {
        -1, 1, 1, -1, 1, 1,
        -1, 1, 1, -1, -1, -1
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

EraserTool::~EraserTool() noexcept{
    glDeleteProgram(prog);
    glDeleteBuffers(1, &VBO);
}
