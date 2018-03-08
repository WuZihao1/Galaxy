#version 430

in vec2 UV;
in vec3 normalWorld;
in vec3 vertexPositionWorld;
in float visibility;

out vec4 daColor;

uniform sampler2D myTextureSampler_1;
uniform sampler2D myTextureSampler_2;
uniform vec3 ambientLight;
uniform vec3 lightPositionWorld;
uniform vec3 eyePositionWorld;
uniform vec3 coefficient_d;
uniform vec3 coefficient_s;
uniform vec3 lightColor;

const vec3 Fog_Real_Color = vec3(0.3, 0.3, 0.3);

void main()
{
	vec3 MaterialAmbientColor = ( 0.5 * texture( myTextureSampler_1, UV) + 0.5 * texture( myTextureSampler_2, UV)).rgb;
	vec3 MaterialDiffuseColor = ( 0.5 * texture( myTextureSampler_1, UV) + 0.5 * texture( myTextureSampler_2, UV)).rgb;
	vec3 MaterialSpecularColor = lightColor;

	vec3 normal = normalize(normalWorld);
	normal = ( 0.5 * texture( myTextureSampler_1, UV) + 0.5 * texture( myTextureSampler_2, UV)).rgb;
	//texture(myTextureSampler_2, UV).rgb;
	normal = normalize(normal * 2.0 - 1.0);

	vec3 lightVectorWorld = normalize(lightPositionWorld - vertexPositionWorld);
	float brightness = dot(lightPositionWorld, normal);
	vec3 diffuseLight = vec3(brightness, brightness, brightness);

	vec3 reflectedLightVectorWorld = reflect(-lightPositionWorld, normal);
	vec3 eyeVectorWorld  = normalize(eyePositionWorld - vertexPositionWorld);
	float s = clamp(dot(reflectedLightVectorWorld, eyePositionWorld), 0, 1);
	s = pow(s, 15);

	vec3 color = MaterialAmbientColor * ambientLight + MaterialDiffuseColor * clamp(diffuseLight, 0, 1) * coefficient_d + MaterialSpecularColor * s * coefficient_s ;
	
	color = mix(Fog_Real_Color, color, visibility);
	
	daColor = vec4(color, 1.0);

}






