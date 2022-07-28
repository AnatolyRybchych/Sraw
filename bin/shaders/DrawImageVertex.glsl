#version 110

attribute vec4 vertex_p;
varying vec2 tex_coord;

void main(){
   tex_coord = vertex_p.xy * 0.5 + vec2(0.5, 0.5);
   gl_Position = vertex_p;
}
