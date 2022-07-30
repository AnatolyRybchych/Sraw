#version 110

attribute vec4 vertex_p;

uniform vec2 scale;
uniform vec2 translate;

varying vec2 frag_coord;

void main(){
    frag_coord = vertex_p.xy;
    gl_Position = (vertex_p + vec4(translate)) * vec4(scale);
}
