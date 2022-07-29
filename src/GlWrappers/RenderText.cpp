#define RENDER_TEXT_IMPLEMENTATION
#include "RenderText.hpp"
#include "ShaderProgram.hpp"

RenderText* RenderText::defaul_instance = nullptr;
FT_Face* RenderText::default_face = nullptr;

RenderText* RenderText::GetDefaultRenderer(){   
    if(defaul_instance == nullptr) throw std::logic_error("use RenderText::InitDefaultRenderer to initialize renderer");
    return defaul_instance;
}
                        
void RenderText::InitDefaultRenderer(const char *font_path){
    if(defaul_instance != nullptr){
        delete defaul_instance;
        defaul_instance = nullptr;
    }
    if(default_face != nullptr) {       
        delete default_face;
        FT_Done_Face(*default_face);
        default_face = nullptr;
    }

    default_face = new FT_Face();
    FT_New_Face(FreeType::GetLib(), font_path, 0, default_face);
    defaul_instance = new RenderText(*default_face);
}

RenderText::RenderText(FT_Face face, const char *attribVertexName, const char *uniformTextureName, const char *uniformTextColor3f, const char *vertex, const char *fragment){
    this->face = face;
    prog = BuildShaderProgram(vertex, fragment);
    vertexPos = glGetAttribLocation(prog, attribVertexName);
    texPos = glGetUniformLocation(prog, uniformTextureName);
    colorPos = glGetUniformLocation(prog, uniformTextColor3f);
}

GLuint RenderText::GetProgram() const noexcept{
    return prog;
}

void RenderText::Render(const __CH_TYPE_ *text, int space, int fontSize, int x, int y, float r, float g, float b) const noexcept{
    FT_Set_Pixel_Sizes(face, 0, fontSize);
    glUseProgram(prog);
    glUniform3f(colorPos, r, g, b);
    render_text(face, text, space, (point){x, y}, vertexPos, texPos);
    glUseProgram(0);
}

int RenderText::GetTextWidth(const __CH_TYPE_ *text, int space, int fontSize) const noexcept{
    FT_Set_Pixel_Sizes(face, 0, fontSize);
    return get_text_width(face, text, space);
}
