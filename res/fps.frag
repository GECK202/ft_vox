#version 410 core

in vec2 a_texCoord;
in float a_number;

out vec4 f_color;

uniform sampler2D u_texture0;


void main(){
    vec4 color = vec4(0,0,0,1);
    if (a_number == 0.0) {
        color.r = 1;
    } else if (a_number == 1.0) {
        color.g = 1;
    } else if (a_number == 2.0) {
        color.b = 1;
    }
	f_color = mix(texture(u_texture0, a_texCoord), color, 0.5);
}