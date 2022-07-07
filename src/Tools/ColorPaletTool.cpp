#include "ColorPaletTool.hpp"
#include "../GlWrappers/ShaderProgram.hpp"
#include "../ResourceProvider.hpp"


void ColorPaletTool::ChangeColor(float relX, float relY) noexcept{
    if(relX < 0 || relX > 1.0 || relY < 0 || relY > 1.0) return;

    int x = relX * paletteCx;
    int y = relY * paletteCy;

    int pixel = (y * paletteCx + x) * 4;

    SetRed(paletteData[pixel + 0] / 255.0);
    SetGreen(paletteData[pixel + 1] / 255.0);
    SetBlue(paletteData[pixel + 2] / 255.0);
}

void ColorPaletTool::OnDraw() const noexcept{
    glUseProgram(prog);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(vertex_pPos);
    glBindTexture(GL_TEXTURE_2D, palette);

    glActiveTexture(GL_TEXTURE0);
    glUniform1i(palettePos, 0);
    
    glUniform3f(colorPos, GetRed(), GetGreen(), GetBlue());
    glUniform2f(viewportPos, (float)GetViewportWidth(),(float)GetViewportHeight());

    glVertexAttribPointer(vertex_pPos, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisableVertexAttribArray(vertex_pPos);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}

void ColorPaletTool::OnDrawCommit() noexcept{
}

void ColorPaletTool::OnResize(int cx, int cy) noexcept{
}

bool ColorPaletTool::OnMouseMove(int x, int y) noexcept{
    if(isMouseDown){
        float rel_x = (x / (float)GetViewportWidth() - 0.5) * 2.0 * (float)GetViewportWidth() / (float)GetViewportHeight(); 
        float rel_y = (y / (float)GetViewportHeight() - 0.5) * 2.0; 
        ChangeColor((rel_x / paleteScale) * 0.5 + 0.5, (rel_y / paleteScale) * 0.5 + 0.5);
        return true;
    }
    return false;
} 

bool ColorPaletTool::OnLMouseDown(int x, int y) noexcept{
    isMouseDown = true;
    OnMouseMove(x, y);
    return true;
}

bool ColorPaletTool::OnLMouseUp(int x, int y) noexcept{
    bool result = OnMouseMove(x, y);
    isMouseDown = false;
    return result;
}

bool ColorPaletTool::OnKeyDown(int vkCode, int repeat) noexcept{
    return false;
}

bool ColorPaletTool::OnKeyUp(int vkCode) noexcept{
    return false;
}

bool ColorPaletTool::OnTextInput(std::wstring str) noexcept{
    return false;
}

bool ColorPaletTool::OnScrollUp() noexcept{
    return false;
}

bool ColorPaletTool::OnScrollDown() noexcept{
    return false;
}


ColorPaletTool::ColorPaletTool(int cx, int cy, CommitHandler &commitHandler, GLuint palette) noexcept
    :DrawingTool(cx, cy, commitHandler),
    palette(palette){
    
    glBindTexture(GL_TEXTURE_2D, palette);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &paletteCx);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &paletteCy);
    glBindTexture(GL_TEXTURE_2D, 0);

    paletteData.resize(paletteCx * paletteCy * 4);
    glGetTextureImage(palette, 0, GL_RGBA, GL_UNSIGNED_BYTE, paletteData.size(), paletteData.data());
    
    r = 0.8;
    g = 0.4;
    b = 0.2;

    isMouseDown = false;

    prog = BuildShaderProgram(
        ResourceProvider::GetProvider().GetPaletteVertex().c_str(),
        ResourceProvider::GetProvider().GetPaletteFragment().c_str()
    );

    vertex_pPos = glGetAttribLocation(prog, "vertex_p");
    colorPos = glGetUniformLocation(prog, "color");
    palettePos = glGetUniformLocation(prog, "palette");
    viewportPos = glGetUniformLocation(prog, "viewport");

    float vertices[] = {
        -1, 1, 1, -1, 1, 1,
        -1, 1, 1, -1, -1, -1
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

ColorPaletTool::~ColorPaletTool() noexcept{
    glDeleteProgram(prog);
    glDeleteBuffers(1, &VBO);
}

float ColorPaletTool::GetRed() const noexcept{
    return r;
}

float ColorPaletTool::GetGreen() const noexcept{
    return g;
}

float ColorPaletTool::GetBlue() const noexcept{
    return b;
}

void ColorPaletTool::SetRed(float value) noexcept{
    r = value;
}

void ColorPaletTool::SetGreen(float value) noexcept{
    g = value;
}

void ColorPaletTool::SetBlue(float value) noexcept{
    b = value;
}


