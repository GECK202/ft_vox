#version 410 core

out vec4 f_color;

in vec3 a_texCoord;

uniform samplerCube u_texture0;

void main()
{
    f_color = texture(u_texture0, a_texCoord);
}