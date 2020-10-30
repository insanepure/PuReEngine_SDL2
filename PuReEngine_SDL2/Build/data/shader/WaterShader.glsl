#version 130

// Interpolated values from the vertex shaders
in vec2 UV;

// Ouput data
out vec4 Fragment;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;
uniform float Time;
uniform vec2 Resolution;

const float PI = 3.1415926535897932;
 
// play with these parameters to custimize the effect
// ===================================================
 
//speed
const float speed = 0.02;
const float speed_x = 0.03;
const float speed_y = 0.03;
 
// refraction
const float emboss = 0.50;
const float intensity = 1.4;
const int steps = 8;
const float frequency = 6.0;
const int angle = 7; // better when a prime
 
// reflection
const float delta = 60.;
const float intence = 700.;
 
const float reflectionCutOff = 0.012;
const float reflectionIntence = 200000.;
 
 
 
  float col(vec2 coord)
  {
    float delta_theta = 2.0 * PI / float(angle);
    float col = 0.0;
    float theta = 0.0;
    for (int i = 0; i < steps; i++)
    {
      vec2 adjc = coord;
      theta = delta_theta*float(i);
      adjc.x += cos(theta)*Time*speed + Time * speed_x;
      adjc.y -= sin(theta)*Time*speed - Time * speed_y;
      col = col + cos( (adjc.x*cos(theta) - adjc.y*sin(theta))*frequency)*intensity;
    }
 
    return cos(col);
  }
 



void main()
{
	vec2 p = UV, c1 = p, c2 = p;
	float cc1 = col(c1);
 
	c2.x += Resolution.x/delta;
	float dx = emboss*(cc1-col(c2))/delta;
 
	c2.x = p.x;
	c2.y += Resolution.y/delta;
	float dy = emboss*(cc1-col(c2))/delta;
 
	c1.x += dx*2.;
	c1.y = -(c1.y+dy*2.);
	Fragment = texture(myTextureSampler,c1);
}

 
