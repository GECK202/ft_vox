#version 410 core

in vec4 a_color;
in vec2 a_texCoord;
in float a_distance;
out vec4 f_color;

uniform sampler2D u_texture0;
uniform vec3 u_fogColor;

void main(){
	vec4 tex_color = texture(u_texture0, a_texCoord);

	float depth = (a_distance/256.0)*(a_distance/256.0)*256.0;

	f_color = mix(mix(a_color*tex_color, tex_color, 0.3), vec4(u_fogColor,1.0), min(1.0, depth/256.0/1.0f));
}