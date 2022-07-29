#include "../ResourceProvider.hpp"
#include "EraserTool.hpp"
#include "../GlWrappers/ShaderProgram.hpp"
#include "../DrawImage.hpp"
#include "../Basics.hpp"

void EraserTool::Erse(int x, int y) const noexcept{
    glUseProgram(prog);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(vertex_pPos);
    glBindTexture(GL_TEXTURE_2D, GetBg().GetGLID()); 
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

void EraserTool::ErseLine(int x1, int y1, int x2, int y2) const noexcept{
    float step = (1.0 - 1.0 / (distance2(x1, y1, x2, y2) + 1.0)) * scale * 0.5;
    for(float progress = 0.0; progress < 1.0; progress += step){
        Erse(lerpi(x1, x2, progress), lerpi(y1, y2, progress));
    }
}

void EraserTool::OnDraw() const noexcept{
    DrawImage::GetRenderer().Draw(GetCommitBuffer().GetGLID());
    Erse(prevX, prevY);
}

bool EraserTool::OnMouseMove(int x, int y) noexcept{
    if(isMouseDown){
        BindFramebuffer(GetCommitBuffer().GetGLID());
        ErseLine(prevX, prevY, x, y);
        UnbindFramebuffer();
    }
    prevX = x;
    prevY = y;
    return true;
} 

bool EraserTool::OnLMouseDown(int x, int y) noexcept{
    isMouseDown = true;
    prevX = x;
    prevY = y;
    BindFramebuffer(GetCommitBuffer().GetGLID());
    Erse(x, y);
    UnbindFramebuffer();
    return true;
}

bool EraserTool::OnLMouseUp(int x, int y) noexcept{
    if(isMouseDown){
        isMouseDown = false;

        Commit();
        ClearCommitBuffer();
    }
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


EraserTool::EraserTool(int cx, int cy, CommitHandler &commitHandler, const Texture &bg) noexcept
    :DrawingTool(cx, cy, commitHandler, bg){

    prog = ResourceProvider::GetProvider().GetErseProgram();

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
