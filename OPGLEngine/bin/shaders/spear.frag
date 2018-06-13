// a simple flat colour shader
#version 410

// input from the last used programmable stage
in vec2 vTexCoord;

// the bound etxture.
//uniform sampler2D texture;
uniform sampler2D diffuseTexture;

// output pixel colour (default if the only out)
out vec4 FragColour;

void main()
{
	// samle the 2D texture,
	// which returns a vec4 with rgba colour data
	FragColour = texture(diffuseTexture, vTexCoord);
}