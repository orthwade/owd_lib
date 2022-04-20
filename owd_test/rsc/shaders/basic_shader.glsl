//----start_gl_vertex_shader----
#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 u_aspect_ratio_projection_matrix;

void main()
{
	gl_Position = u_aspect_ratio_projection_matrix * position;
}
//----end_gl_vertex_shader----



//----start_gl_fragment_shader----
#version 330 core

layout(location = 0) out vec4 colour;

uniform vec4 u_colour;

void main()
{
	colour = u_colour;
}
//----end_gl_fragment_shader----