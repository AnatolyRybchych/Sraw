#version 110

uniform float circle_scale;
uniform vec2 viewport;
varying vec2 frag_coord;

void main(){
    float alpha = clamp((1.0 - distance(frag_coord / vec2((viewport.y / viewport.x) * circle_scale,  circle_scale), vec2(0, 0))) * viewport.y * 0.5, 0.5, 0.8);
    gl_FragColor = vec4(0.0, 0.0, 0.0, alpha);
}