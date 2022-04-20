#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texture_coordinates;

out vec2 v_texture_coordinates;

uniform mat4 u_aspect_ratio_projection_matrix;

void main()
{
	gl_Position =  u_aspect_ratio_projection_matrix * position;
	v_texture_coordinates = texture_coordinates;
}