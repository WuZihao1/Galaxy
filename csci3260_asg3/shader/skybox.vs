#version 440

in layout (location = 0) vec3 position;
out vec3 TexCoords;
out float visibility;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 M;
uniform int fog_flag;

const float FogDensity = 0.05f;
const float FogGradient = 10.0f;

void main()
{

	mat4 V = view;
	V[0][3] = 0.0f;
	V[1][3] = 0.0f;
	V[2][3] = 0.0f;
	vec4 pos = projection * V * M * vec4(position, 1.0);
	gl_Position = pos;

	TexCoords = position;


	
	if(fog_flag==1)
	{
		float distance = length((view * M * vec4(position, 1.0f)));
		visibility = exp(-pow((distance * FogDensity), FogGradient));
		visibility = clamp(visibility, 0.0f, 1.0f);
		visibility = 1.0-visibility;
	}
	else visibility=1;
}