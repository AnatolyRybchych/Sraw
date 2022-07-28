#version 110

uniform vec3 color;
uniform vec2 viewport;
uniform sampler2D palette; 

varying vec2 frag_coord;

void main(){
    vec2 palette_uv = vec2((frag_coord.x* viewport.x / viewport.y + 0.5) , (0.5 - frag_coord.y));
    vec2 coord = vec2(frag_coord.x * viewport.x / viewport.y, frag_coord.y) * 2.0;

    vec3 result = texture2D(palette, palette_uv).xyz;

    float alpha = 1.0;
    if(coord.x < -1.0 || coord.x > 1.0 || coord.y < -1.0 || coord.y > 1.0){
        result = color;
        alpha = (sqrt(2.0) - distance(vec2(0.0, 0.0), coord)) * 10.0;
        alpha = clamp(alpha, 0.0, 1.0);
    }
    gl_FragColor = vec4(mix(vec3(0.0, 0.0, 0.0), result, alpha), max(alpha, 0.5));
}
