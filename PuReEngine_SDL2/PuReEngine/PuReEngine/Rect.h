#pragma once
#include "Defines.h"
#include "Vector2.h"
namespace PuRe 
{
	class Rect
	{
	public:
		//Variables
		float32 Width,Height;
		Vector2 Position;
		//Constructors
		Rect();
		Rect(float32 X,float32 Y,float32 Width,float32 Height);
    Rect(Vector2 Position, float32 Width, float32 Height);
		//Methods
		bool Intersects(Rect* Rectangle);
		int16 IntersectSide(Rect* Rectangle);
	};
}

