#version 410 core

layout (location = 0) in vec2 v_position;
layout (location = 1) in float v_number;

out vec2 a_texCoord;

uniform float u_fps;
uniform float u_ar;
uniform float u_scale;

void main(){
    float step = 1.0 / 16.0;
    float step3 = step * u_scale * u_ar / 3.0;
    a_texCoord = (v_position + 1.0)/2.0;
    a_texCoord.x *= step;
    vec2 pos = v_position;
    
    pos = vec2((pos.x - 1.0) * u_ar, pos.y);
    pos *= ((u_scale * 0.2) * step);
 
    if (v_number == 0.0) {  
        a_texCoord.x += (step * floor(u_fps / 100.0));
        pos.x += step3;
    }
    else if (v_number == 1.0) {
        a_texCoord.x += (step * mod(floor(u_fps / 10.0), 10.0));
        pos.x += (step3*2);
    }
    else if (v_number == 2.0){
        a_texCoord.x += (step * mod(mod(u_fps, 100.0), 10.0));
        pos.x += (step3*3);
    } else {
        pos.x *= 6.0;
        pos.x += step3 *3;
        a_texCoord.x *= 6.0;
        a_texCoord.x += (step * 10);
    }

    pos.y += (1.0 - step3);
    
	gl_Position = vec4(pos, 0.0, 1.0);
}