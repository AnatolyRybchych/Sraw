#version 110

varying vec2 frag_coord;
uniform vec2 pos;
uniform vec3 color;
uniform float max_darkness;
uniform float power;
uniform float untouched_radius;

void main(){
   float fragPower = distance(frag_coord, pos) - untouched_radius;
   fragPower = fragPower >= 0.0 ? fragPower * power : fragPower;
   fragPower = fragPower > max_darkness ? max_darkness : fragPower;
   gl_FragColor = vec4(color, fragPower);
}
