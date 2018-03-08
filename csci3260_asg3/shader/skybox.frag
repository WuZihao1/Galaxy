#version 440

in vec3 TexCoords;
out vec4 FinalColor;
in float visibility;

uniform samplerCube skybox;
uniform int color_flag;

void main()
{
	vec4 color = texture(skybox,TexCoords);
	vec4 Fog_Real_Color;
		if(color_flag == 0)
		{
			Fog_Real_Color = vec4(0.5f,0.5f,0.5f,1.0f);
		}

		else 
		{	
			Fog_Real_Color = vec4(0.7f,0.0f,0.0f,1.0f);
		}

	vec4 daColor = mix(Fog_Real_Color,color,visibility);
	FinalColor = daColor;
}