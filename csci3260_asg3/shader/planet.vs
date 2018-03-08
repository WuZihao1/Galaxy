#version 440
in layout(location = 0) vec3 vertexPosition_modelspace;
in layout(location = 1) vec2 vertexUV;
in layout(location = 2) vec3 normal;


const float FogDensity = 0.05;
const float FogGradient = 3.5;

uniform mat4 PM;
uniform mat4 MM;
uniform mat4 VM;
uniform int fog_flag;

out vec3 normalWorld;
out vec2 UV;
out vec3 vertexPositionWorld;
out float visibility;


void main()
{
    vec4 v = vec4(vertexPosition_modelspace, 1.0);
	vec4 newPosition = MM * v;
	vec4 projectedPosition = PM * VM * newPosition;
	gl_Position = projectedPosition;
		
	vec4 normal_temp = MM * vec4(normal, 0);
	normalWorld = normal_temp.xyz;

	vertexPositionWorld = newPosition.xyz;
	UV = vertexUV;

	if(fog_flag==1)
	{
		float distance = length((VM * MM * vec4(vertexPosition_modelspace, 1)));
		visibility = exp(-pow((distance * FogDensity), FogGradient));
		visibility = clamp(visibility, 0.0, 1.0);
	}
	else visibility = 1;




}