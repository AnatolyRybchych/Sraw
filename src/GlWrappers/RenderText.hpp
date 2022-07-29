#pragma once
#define RENDER_WCHAR
#include "FreeType.hpp"
#define GL_H <GL/glew.h>
#include "render_text.h"
#include <stdexcept>

constexpr const char *RenderTextDefaultVertex = 
"#version 110\n"
"\n"
"attribute vec4 vertex_p;\n"
"varying vec2 tex_coord;\n"
"\n"
"void main(){\n"
"   tex_coord = vec2(vertex_p.x * 0.5 + 0.5, 1.0 - (vertex_p.y * 0.5 + 0.5));\n"
"   gl_Position = vertex_p;\n"
"}\n"
;

constexpr const char *RenderTextDefaultFragment = 
"#version 110\n"
"\n"
"uniform sampler2D tex;\n"
"uniform vec3 color;\n"
"varying vec2 tex_coord;\n"
"\n"
"void main(){\n"
"   float text_mask = texture2D(tex, tex_coord).r;\n"
"   gl_FragColor = vec4(color, text_mask);\n"
"}\n"
;

class RenderText{
private:
    FT_Face face;

    GLuint prog;

    GLint vertexPos;
    GLint texPos;
    GLint colorPos;

    static RenderText* defaul_instance;
    static FT_Face *default_face;
    
public:
    static RenderText* GetDefaultRenderer();
    static void InitDefaultRenderer(const char *font_path);
    RenderText(FT_Face face, const char *attribVertexName = "vertex_p", const char *uniformTextureName = "tex", const char *uniformTextColor3f = "color", const char *vertex = RenderTextDefaultVertex, const char *fragment = RenderTextDefaultFragment);
    GLuint GetProgram() const noexcept;
    void Render(const __CH_TYPE_ *text, int space, int fontSize, int x, int y, float r = 0.6666, float g = 0.6666, float b = 1.0) const noexcept;
    int GetTextWidth(const __CH_TYPE_ *text, int space, int fontSize) const noexcept;
};
