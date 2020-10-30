#version 130

// Interpolated values from the vertex shaders
in vec2 UV;

// Ouput data
out vec4 Fragment;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;
uniform float Time;
uniform vec2 Resolution;

 


void main()
{
	vec2 p = UV + 0.005*vec2( sin(Time+1024.0*UV.x),cos(Time+768.0*UV.y));
	Fragment = texture(myTextureSampler, p);
	Fragment.r = 1.0;
}

 
