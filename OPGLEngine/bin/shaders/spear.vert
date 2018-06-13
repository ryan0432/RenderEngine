// bunny vertex shader
#version 410

// input from the vertex buffer, not passed to other stages by default
layout(location = 0) in vec4 Position;

// input from the vertex shader that we will pass as a custom output
layout(location = 2)in vec2 TexCoord;

// output that goes to the next used programmable stage
out vec2 vTexCoord;

uniform mat4 ProjectionViewModel;


void main()
{
	// simply pass through the variable
	vTexCoord = TexCoord;
	gl_Position = ProjectionViewModel * Position;
}
