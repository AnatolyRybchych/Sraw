#version 110

#define PI 3.14159

uniform sampler2D tex;
uniform vec2 viewport;
uniform float circle_scale;
uniform float alpha;
uniform int segment_count;
uniform int segment;
uniform int is_mouse_over;

varying vec2 frag_coord;
varying vec2 tex_coord;

void main(){
    vec4 tex_data = texture2D(tex, tex_coord);
    
    vec3 color;
    float alpha_mask;
     

    float viewport_mask = (1.0 - distance(vec2(0.0, 0.0), frag_coord * circle_scale * 1.1) / (circle_scale * circle_scale)) * viewport.y * 0.01;
    float body_mask = min(min(viewport_mask, tex_data.r), tex_data.a);
    float outline_mask = min(body_mask, tex_data.g);
    

    if(is_mouse_over != 0){
        vec3 color_body = vec3(0.6666, 0.6666, 1.0);
        vec3 color_outline = vec3(0.6666, 0.6666, 1.0);
         
        vec3 color_glow = vec3(0.9, 0.8, 1.0);    
        
        float glow_mask = min(min(tex_data.b, viewport_mask), tex_data.a);

        alpha_mask = body_mask + outline_mask + glow_mask;
        color = mix(color_body * body_mask, color_outline, outline_mask);
        color = mix(color, color_glow, glow_mask); 
    }
    else{
        vec3 color_body = vec3(0.3, 0.3, 0.6);    
        vec3 color_outline = vec3(0.6666, 0.6666, 1.0);

        alpha_mask = body_mask + outline_mask;
        color = mix(color_body * body_mask, color_outline, outline_mask);
    }

    gl_FragColor = vec4(color, alpha_mask);
}