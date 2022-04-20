#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 u_aspect_ratio_projection_matrix;

void main()
{
	gl_Position =  u_aspect_ratio_projection_matrix * position;
}