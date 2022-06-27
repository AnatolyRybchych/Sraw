#version 110

uniform vec3 color;
uniform vec2 viewport;
uniform float scale; 
uniform float power; 

varying vec2 frag_coord;

void main(){
    vec2 circle_coord = vec2(frag_coord.x * viewport.x / viewport.y, frag_coord.y);
    gl_FragColor = vec4(color, (1.0 - distance(vec2(0.0, 0.0), circle_coord)) * viewport.y * power * scale);
}
