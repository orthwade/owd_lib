//----start_gl_vertex_shader----
#version 330 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec2 a_texture_coordinates;
layout(location = 2) in float a_texture_index;

out vec2 v_texture_coordinates;
out float v_texture_index;

uniform mat4 u_aspect_ratio_projection_matrix;

void main()
{
	gl_Position =  u_aspect_ratio_projection_matrix * a_position;
	v_texture_coordinates = a_texture_coordinates;
	v_texture_index = a_texture_index;
}
//----end_gl_vertex_shader----



//----start_gl_fragment_shader----
#version 330 core

layout(location = 0) out vec4 colour;

uniform sampler2D u_textures[128];

in vec2 v_texture_coordinates;
in float v_texture_index;

void main()
{
	int texture_index = int(v_texture_index);
	colour = texture(u_textures[texture_index], v_texture_coordinates);
}
//----end_gl_fragment_shader----