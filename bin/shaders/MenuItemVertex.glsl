#version 110

attribute vec4 vertex_p;

uniform vec2 viewport;
uniform float circle_scale;
uniform float alpha;
uniform int segment_count;
uniform int segment;
uniform int is_mouse_over;

varying vec2 frag_coord;
varying vec2 tex_coord;

void main(){
    gl_Position = vertex_p;
    gl_Position.xy += vec2(sin(alpha), cos(alpha));
    gl_Position.y *= circle_scale * 0.5;
    gl_Position.x *= circle_scale * 0.5 * viewport.y / viewport.x;
    frag_coord = vertex_p.xy;
    tex_coord = vec2(vertex_p.x / circle_scale * 0.5 + 0.5, 0.5 - vertex_p.y / circle_scale * 0.5);
}