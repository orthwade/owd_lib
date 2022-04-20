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

layout(location = 0) out vec4 o_colour;

void main()
{
	o_colour = vec4(1.0);
}
//----end_gl_fragment_shader----