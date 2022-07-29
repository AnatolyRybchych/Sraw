#version 110
attribute vec4 vertex_p;
varying vec2 frag_coord;

void main(){
   frag_coord = vertex_p.xy;
   gl_Position = vertex_p;
}
