#version 410 core

in vec4 a_color;
in vec2 a_texCoord;
in float a_distance;

out vec4 f_color;

uniform sampler2D u_texture0;
uniform vec3 u_fogColor;

void main(){
	vec4 tex_color = texture(u_texture0, a_texCoord);
	if (tex_color.a < 0.5)
		discard;
	float depth = a_distance;
	f_color = mix(a_color * tex_color, vec4(u_fogColor,1.0), 0);//min(1.0, a_distance/255.0));
}