#version 110

#define BG_CONTRAST 0.4

uniform vec2 scale;
uniform vec3 color;
uniform vec2 translate;
uniform vec2 vp_size;

varying vec2 frag_coord;

float width(float y){
    return pow(sin((1.0 - y) * 1.5707), 0.2);
}

float over(float x, float y){
    return clamp(min(width(y) - abs(x), 1.0 - abs(y)) * vp_size.x * 0.5, 0.0, 1.0);
}

void main(){
    float brightness = (color.r + color.g + color.b) / 3.0;
    float bg_offset;
    if(brightness > 0.5) bg_offset = -BG_CONTRAST;
    else bg_offset = BG_CONTRAST;

    vec3 bg_color = color + vec3(bg_offset, bg_offset, bg_offset);

    float bg_mask = over(frag_coord.x * 1.1, frag_coord.y * 1.1);
    float outline_mask = over(frag_coord.x, frag_coord.y) - bg_mask;
    gl_FragColor = vec4(bg_color, max(bg_mask, outline_mask));
    gl_FragColor.rgb = mix(bg_color.rgb, color.rgb, clamp(outline_mask, 0.0, 1.0));
}