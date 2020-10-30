#version 330 core

in vec2 UV;

uniform sampler2D myTextureSampler;
uniform vec4 Color = vec4( 1.0, 1.0, 1.0, 1.0 );
uniform float Time;
uniform vec2 Resolution;

out vec4 Fragment;


void main()
{ 
	Fragment = texture(myTextureSampler,UV)*Color;
}