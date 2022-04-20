//----start_gl_vertex_shader----
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_colour;
uniform mat4 u_aspect_ratio_projection_matrix;

out vec4 v_colour;

void main()
{
	v_colour = a_colour;
	gl_Position = u_aspect_ratio_projection_matrix * vec4(a_position, 1.0);
}
//----end_gl_vertex_shader----



//----start_gl_fragment_shader----
#version 330 core
layout(location = 0) out vec4 colour;

in vec4 v_colour;

void main()
{
	colour = v_colour;
}
//----end_gl_fragment_shader----