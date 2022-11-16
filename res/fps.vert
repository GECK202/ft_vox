#version 410 core

layout (location = 0) in vec2 v_position;
layout (location = 1) in float v_number;

out vec2 a_texCoord;
out float a_number;

uniform float u_fps;
uniform float u_ar;
uniform float u_scale;

void main(){
    a_texCoord = (v_position + 1.0)/2.0;
    a_texCoord.x /= 16.0;
    vec2 pos = v_position;
    pos = vec2((pos.x - 1.0) * u_ar, pos.y);
    pos *= ((u_scale * 0.2) / 16.0);
    
 
    if (v_number == 0.0) {  
        a_texCoord.x += ((1.0/16.0) * mod(mod(u_fps, 100.0), 10.0));
        pos.y += 0.1;
    }
    else if (v_number == 1.0) {
        a_texCoord.x += ((1.0/16.0) * mod(round(u_fps / 10.0), 10.0));
        pos.y += 0.2;
    }
    else if (v_number == 2.0){
        a_texCoord.x += ((1.0/16.0) * round(u_fps / 100.0));
        pos.y += 0.3;
    } else {
        pos.x *= 3.0;
        a_texCoord.x *= 3.0;
        a_texCoord.x += ((1.0/16.0) * 10);
    }
    a_number = v_number;
    //pos += (0.1 * v_number);
	gl_Position = vec4(pos, 0.0, 1.0);
}