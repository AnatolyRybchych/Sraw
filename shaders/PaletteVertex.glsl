#version 110

attribute vec4 vertex_p;

uniform vec2 viewport; 

varying vec2 frag_coord;

void main(){
    gl_Position = vertex_p;

    frag_coord = vertex_p.xy;
}
