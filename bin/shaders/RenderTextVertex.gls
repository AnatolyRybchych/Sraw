#version 110

attribute vec4 vertex_p;
varying vec2 tex_coord;

void main(){
   tex_coord = vec2(vertex_p.x * 0.5 + 0.5, 1.0 - (vertex_p.y * 0.5 + 0.5));
   gl_Position = vertex_p;
}