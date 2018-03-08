#version 440

in vec3 normalWorld;
in vec2 UV;
in vec3 vertexPositionWorld;
in float visibility;


out vec4 FinalColor;

uniform sampler2D myTextureSampler_1;
uniform vec3 ambientLight;
uniform vec3 coefficient_d;
uniform vec3 coefficient_s;
uniform vec3 eyePositionWorld;
uniform vec3 lightPositionWorld;
uniform int normal_flag;
uniform vec3 lightColor;
uniform int color_flag;


uniform vec3 coefficient_d_2;
uniform vec3 coefficient_s_2;
uniform vec3 lightPositionWorld_2;


void main()
{
	
	
		vec3 normal = normalize(normalWorld);
		vec3 lightVectorWorld = normalize(lightPositionWorld - vertexPositionWorld);
		float brightness = dot(lightVectorWorld , normal);
		vec3 diffuseLight = vec3(brightness,brightness, brightness);

		vec3 lightVectorWorld_2 = normalize(lightPositionWorld_2 - vertexPositionWorld);
		float brightness_2 = dot(lightVectorWorld , normal);
		vec3 diffuseLight_2 = vec3(brightness_2,brightness_2, brightness_2);

		vec3 reflectedLightVectorWorld = reflect(-lightVectorWorld, normalize(normal));
		vec3 eyeVectorWorld = normalize(eyePositionWorld - vertexPositionWorld);
		float s = clamp(dot(reflectedLightVectorWorld , eyeVectorWorld) , 0 , 1);

		vec3 reflectedLightVectorWorld_2 = reflect(-lightVectorWorld_2, normalize(normal));
		vec3 eyeVectorWorld_2 = normalize(eyePositionWorld - vertexPositionWorld);
		float s_2 = clamp(dot(reflectedLightVectorWorld_2 , eyeVectorWorld_2) , 0 , 1);


		s = pow(s,coefficient_s[0]);
		vec3 MaterialAmbientColor = texture2D(myTextureSampler_1,UV).rgb;
		vec3 MaterialDiffuseColor = texture2D(myTextureSampler_1,UV).rgb;
		vec3 MaterialSpecularColor = lightColor;
		vec3 color_1 = MaterialAmbientColor * ambientLight + MaterialDiffuseColor * clamp(diffuseLight,0,1) * coefficient_d + MaterialSpecularColor* coefficient_s * s ;
		
		s_2 = pow(s,coefficient_s_2[0]);
		vec3 MaterialAmbientColor_2 = texture2D(myTextureSampler_1,UV).rgb;
		vec3 MaterialDiffuseColor_2 = texture2D(myTextureSampler_1,UV).rgb;
		vec3 MaterialSpecularColor_2 = lightColor;
		vec3 color_2 = MaterialAmbientColor_2 * ambientLight + MaterialDiffuseColor_2 * clamp(diffuseLight_2,0,1) * coefficient_d_2 + MaterialSpecularColor_2* coefficient_s_2 * s_2 ;
		
		vec3 color = color_1*0.5+color_2*0.5;
	
		
		vec3 Fog_Real_Color;
		if(color_flag == 0)
		{
			Fog_Real_Color = vec3(0.5f,0.5f,0.5f);
		}

		else 
		{
			Fog_Real_Color = vec3(0.7f,0.0f,0.0f);
		}

		vec3 daColor = mix(Fog_Real_Color,color,visibility);
		FinalColor = vec4(daColor,1.0);
	
	
	


}
