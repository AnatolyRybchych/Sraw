#version 110

attribute vec4 vertex_p;

uniform vec2 pos;
uniform vec2 viewport; 
uniform float scale; 

varying vec2 tex_coord;

void main(){
    gl_Position = vertex_p;
    gl_Position.x *= viewport.y / viewport.x;
    gl_Position.xy *= scale;
    gl_Position.xy += pos;
    
    tex_coord = vec2(gl_Position.x + 1.0, gl_Position.y + 1.0) * 0.5;
}
