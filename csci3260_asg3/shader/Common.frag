#version 430

in vec3 normalWorld;
in vec2 UV;
in vec3 vertexPositionWorld;

out vec4 daColor;

uniform sampler2D myTextureSampler_1;
uniform sampler2D myTextureSampler_2;
uniform vec3 ambientLight;
uniform vec3 coefficient_d;
uniform int coefficient_s;
uniform vec3 eyePositionWorld;
uniform vec3 lightPositionWorld;

void main()
{
	vec3 lightVectorWorld = normalize(lightPositionWorld - vertexPositionWorld);
	float brightness = dot(lightVectorWorld , normalize(normalWorld));
	vec4 diffuseLight = vec4(brightness,brightness, brightness, 1.0);

	vec3 reflectedLightVectorWorld = reflect(-lightVectorWorld, normalWorld);
	vec3 eyeVectorWorld = normalize(eyePositionWorld - vertexPositionWorld);
	float s = clamp(dot(reflectedLightVectorWorld , eyeVectorWorld) , 0 , 1);


	s = pow(s,coefficient_s);

	vec3 MaterialAmbientColor = texture(myTextureSampler_1,UV).rgb * 0.5+ texture(myTextureSampler_2,UV).rgb*0.5;
	vec3 MaterialDiffuseColor = texture(myTextureSampler_2,UV).rgb * 0.5+ texture(myTextureSampler_2,UV).rgb*0.5;
	vec3 MaterialSpecularColor = vec3(0.3,0.3,0.3);
	vec3 color = ambientLight * MaterialAmbientColor + MaterialDiffuseColor * clamp(diffuseLight,0,1) * coefficient_d + MaterialSpecularColor * s ;


	daColor = vec4(color,1.0);

}
