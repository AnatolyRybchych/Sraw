#version 110

uniform sampler2D tex;
uniform vec3 color;
varying vec2 tex_coord;

void main(){
   float text_mask = texture2D(tex, tex_coord).r;
   gl_FragColor = vec4(color, text_mask);
}