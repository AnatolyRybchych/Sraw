#version 110

attribute vec4 vertex_p;

uniform vec2 pos;
uniform vec2 viewport; 
uniform float scale; 

varying vec2 frag_coord;

void main(){
    gl_Position = vertex_p;
    gl_Position.xy *= scale;
    gl_Position.xy += pos;

    frag_coord = vertex_p.xy;
}
