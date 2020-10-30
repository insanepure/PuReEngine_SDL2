#version 330 core

in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

in vec3 VertexPosition; 
uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
uniform float Time;

void main() 
{ 
	gl_Position = vec4( VertexPosition, 1 ); 
	UV = vertexUV;
}