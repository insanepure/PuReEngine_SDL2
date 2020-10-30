#version 330 core

in vec2 UV;

uniform sampler2D myTextureSampler;
uniform vec4 Color = vec4( 1.0, 1.0, 1.0, 1.0 );
uniform float Time;
uniform vec2 Resolution;

out vec4 Fragment;

void main()
{ 
	vec4 textColor = texture(myTextureSampler,UV);
	float greyscale = dot(textColor.rgb,vec3(0.3, 0.59, 0.11));
	Fragment = vec4(greyscale,greyscale,greyscale,textColor.a)*Color;
}