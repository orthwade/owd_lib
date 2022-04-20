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