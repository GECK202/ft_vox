#version 410 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_texCoord;
layout (location = 2) in vec4 v_light;

out vec4 a_color;
out vec2 a_texCoord;
out float a_distance;

uniform mat4 u_model;
uniform mat4 u_proj;
uniform mat4 u_view;
uniform vec3 u_skyLightColor;
uniform vec3 u_cameraPos;
uniform float u_gamma;

void main(){
	vec4 position = u_proj * u_view * u_model * vec4(v_position, 1.0);
	a_color = vec4(v_light.r,v_light.g,v_light.b,1.0f);
	a_texCoord = v_texCoord;
	a_color.rgb += v_light.a;
	a_color.rgb *= 1.0-position.z*0.0025;
	a_color.rgb = pow(a_color.rgb, vec3(1.0/0.7));
	a_distance = length(position);
	gl_Position = position;
}