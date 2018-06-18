// a simple flat colour shader
#version 410

// input from the last used programmable stage
in vec2 vTexCoord;
in vec4 vPosition;
in vec3 vNormal;

// uniform sampler2D texture;
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

uniform vec3 Ka; // ambient material colour
uniform vec3 Kd; // diffuse material colour
uniform vec3 Ks; // specular material colour
uniform float specularPower; // material specular power

uniform vec3 Ia; // ambient light colour
uniform vec3 Id1; // diffuse light colour
uniform vec3 Is1; // specular light colour

uniform vec3 Id2; // diffuse light colour
uniform vec3 Is2; // specular light colour

uniform vec3 LightDirection01; // light direction
uniform vec3 LightDirection02; // light direction

uniform vec3 cameraPosition;

// output pixel colour (default if the only out)
out vec4 FragColour;

void main()
{
	// ensure normal and light direction are normalised
	vec3 N = normalize(vNormal);
	vec3 L01 = normalize(LightDirection01);
	vec3 L02 = normalize(LightDirection02);
	// calculate lambert term (negate light direction)
	float lambertTerm01 = max( 0, min( 1, dot( N, -L01 ) ) );
	float lambertTerm02 = max( 0, min( 1, dot( N, -L02 ) ) );
	// calculate view vector and reflection vector
	vec3 V = normalize(cameraPosition - vPosition.xyz);
	vec3 R01 = reflect( L01, N );
	vec3 R02 = reflect( L02, N );
	// calculate specular term
	float specularTerm01 = pow( max( 0, dot( R01, V ) ), specularPower );
	float specularTerm02 = pow( max( 0, dot( R02, V ) ), specularPower );
	// calculate diffuse
	vec3 ambient = Ia * Ka;
	
	vec3 diffuse1 = Id1 * Kd * lambertTerm01;
	vec3 specular1 = Is1 * Ks * specularTerm01;
	
	vec3 diffuse2 = Id2 * Kd * lambertTerm02;
	vec3 specular2 = Is2 * Ks * specularTerm02;
	// sample the 2D texture,
	// which returns a vec4 with rgba colour data
	FragColour = vec4(ambient + diffuse1 + diffuse2 + specular1 + specular2, 1) *
					texture(diffuseTexture, vTexCoord) *
					texture(specularTexture, vTexCoord);
}