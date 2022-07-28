#version 110

uniform sampler2D bg; 

varying vec2 tex_coord;

void main(){
    gl_FragColor = texture2D(bg, tex_coord);
}