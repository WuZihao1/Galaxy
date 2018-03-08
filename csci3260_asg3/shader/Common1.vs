#version 430

in layout(location = 0) vec3 vertexPosition_modelspace;
in layout(location = 1) vec2 vertexUV;
in layout(location = 2) vec3 normal;

uniform mat4 PM;
uniform mat4 MM;
uniform mat4 VM;
uniform float Fog_Flag;

out vec3 normalWorld;
out vec2 UV;
out vec3 vertexPositionWorld;
out float visibility;

const float FogDensity = 0.04;
const float FogGradient = 2.5;

void main()
{
	vec4 v = vec4(vertexPosition_modelspace, 1.0);
	gl_Position = PM * VM * MM * v;
	
	vec4 normal_temp = MM * vec4(normal, 0);
	normalWorld = normal_temp.xyz;
	
	UV = vertexUV;

	vec4 newPosition = MM * v;
	vertexPositionWorld = newPosition.xyz;

	if(Fog_Flag == 1)
	{
		float distance = length((VM * MM * vec4(vertexPosition_modelspace, 1)));
		visibility =exp(-pow( (distance * FogDensity),  FogGradient) );
		visibility = clamp(visibility, 0, 1);
	}
	else visibility = 1;
	
}



