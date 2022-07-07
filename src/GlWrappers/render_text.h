#ifndef __REDNER_TEXT_H_
#define __REDNER_TEXT_H_
/*
write
#define RENDER_TEXT_IMPLEMENTATION
before including header file
*/

#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H

typedef struct point{
    int x, y;
} point;

typedef struct viewport{
    int x, y, width, heigth;
} viewport;


//renders text using current shader program
//without buffering previous characters
void render_text(FT_Face face, const char *text, int space, point pos, const viewport *viewport, GLint attrib_vertex_pos, GLint uniform_texture);


#ifdef RENDER_TEXT_IMPLEMENTATION

static void draw_quad_VBO(GLint attrib_VBO);

//VBO
static GLuint quad_VBO;
static GLuint _init_quad_VBO();
static GLuint _get_quad_VBO();
static GLuint (*get_quad_VBO)() = _init_quad_VBO;
//VBO

//Texture
static GLuint char_texture;
static GLuint _init_char_texture();
static GLuint _get_char_texture();
static GLuint (*get_char_texture)() = _init_char_texture;
//Texture



void render_text(FT_Face face, const char *text, int space, point pos, const viewport *viewport, GLint attrib_vertex_pos, GLint uniform_texture){

    int cur_x = pos.x;

    const char *text_ptr = text;
    char curr;
    char prev = 0;
    while(curr = *(text_ptr++)){
        
        FT_Load_Char(face, curr, FT_LOAD_RENDER);
        FT_GlyphSlot glyph = face->glyph;

        if(curr != prev){
            glBindTexture(GL_TEXTURE_2D, get_char_texture());
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, glyph->bitmap.width, glyph->bitmap.rows, 
                                        0, GL_RED, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);

            glActiveTexture(GL_TEXTURE0);
            glUniform1i(uniform_texture, 0);
        }

        glViewport(
            viewport->x + cur_x + glyph->metrics.horiBearingX / 64, 
            viewport->heigth - viewport->y - pos.y - glyph->metrics.vertAdvance / 64, 
            glyph->metrics.horiAdvance / 64,
            glyph->metrics.height / 64
        );

        draw_quad_VBO(attrib_vertex_pos);

        cur_x += glyph->metrics.horiAdvance / 64 + space;

        if(cur_x > viewport->width + viewport->x) break;

        prev = curr;
    }

    glViewport(
        viewport->x,
        viewport->y,
        viewport->width,
        viewport->heigth
    );
}

void draw_quad_VBO(GLint attrib_VBO){
    glBindBuffer(GL_ARRAY_BUFFER, get_quad_VBO());
    glEnableVertexAttribArray(attrib_VBO);
    glVertexAttribPointer(attrib_VBO, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}



//VBO
static GLuint _init_quad_VBO(){
    static float quad_VBO_data[12] = {
        -1, 1, 1, -1, 1, 1,
        -1, 1, 1, -1, -1, -1
    };

    glGenBuffers(1, &quad_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, quad_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_VBO_data), quad_VBO_data, GL_STATIC_DRAW);

    get_quad_VBO = _get_quad_VBO;
    return get_quad_VBO();
}

static GLuint _get_quad_VBO(){
    return quad_VBO;
}
//VBO




//Textue
static GLuint _init_char_texture(){
    glGenTextures(1, &char_texture);
    glBindTexture(GL_TEXTURE_2D, char_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    get_char_texture = _get_char_texture;
    return get_char_texture();
}

static GLuint _get_char_texture(){
    return char_texture;
}
//Texture
#endif
#endif
