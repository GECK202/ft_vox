#version 410 core

layout (location = 0) in vec3 v_position;

out vec3 a_texCoord;

uniform mat4 u_proj;
uniform mat4 u_view;


void main()
{
    mat4 viewMat = mat4(mat3(u_view));
    vec4 view = viewMat * vec4(800.00*v_position,1.0);
    a_texCoord = v_position;
    vec4 pos = view;
    gl_Position = u_proj * vec4(pos.xyzw);
}  