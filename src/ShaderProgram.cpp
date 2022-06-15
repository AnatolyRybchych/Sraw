#include "ShaderProgram.hpp"
#include <iostream>

GLuint BuildShaderProgram(const char *vertexSrc, const char *fragmentSrc){
    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint prog = glCreateProgram();

    glShaderSource(vert, 1, &vertexSrc, nullptr);
    glShaderSource(frag, 1, &fragmentSrc, nullptr);

    glCompileShader(vert);
    glCompileShader(frag);

    glAttachShader(prog, vert);
    glAttachShader(prog, frag);

    glLinkProgram(prog);

    GLint status;
    glGetProgramiv(prog, GL_LINK_STATUS, &status);

    if(!status){
        constexpr int msgLen = 1000;
        char msg[msgLen];
        glGetProgramInfoLog(prog, msgLen, nullptr, msg);
        std::cout<<"shader program error:"<<msg<<std::endl;

        glGetShaderiv(vert, GL_COMPILE_STATUS, &status);
        if(!status){
            glGetShaderInfoLog(vert, msgLen, nullptr, msg);
            std::cout<<"vertex shader error:"<<msg<<std::endl;
        }

        glGetShaderiv(frag, GL_COMPILE_STATUS, &status);
        if(!status){
            glGetShaderInfoLog(frag, msgLen, nullptr, msg);
            std::cout<<"fragment shader error:"<<msg<<std::endl;
        }
    }
    glDeleteShader(vert);
    glDeleteShader(frag);
    return prog;
}
