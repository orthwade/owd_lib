//----start_gl_vertex_shader----
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
//----end_gl_vertex_shader----



//----start_gl_fragment_shader----
#version 330 core

layout(location = 0) out vec4 colour;

uniform vec4 u_colour;
uniform sampler2D u_texture;

in vec2 v_texture_coordinates;

void main()
{
	vec4 texture_colour = texture(u_texture, v_texture_coordinates);
	colour = texture_colour;
	//colour = u_colour;
}
//----end_gl_fragment_shader----