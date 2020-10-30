#pragma once
#include "Defines.h"
#include <cmath>
namespace PuRe 
{
	class Vector2
	{
	public:
		//Variables
		float32 X,Y;
		//Standard Constructor
		Vector2();
		//Constructors
		Vector2(float32 rhs);
		Vector2(float32 X,float32 Y);
		Vector2(Vector2 const& rhs);
		//Methods
		void normalize();
		float32 length();
		float32 Dot(const Vector2& vec2);
		float32 Distance(const Vector2& vec2);
		// Operators that change this Object
		Vector2& Vector2::operator= (Vector2 const& rhs);
		Vector2& Vector2::operator+= (Vector2 const& rhs);
		Vector2& Vector2::operator-= (Vector2 const& rhs);
		Vector2& Vector2::operator/= (Vector2 const& rhs);
		Vector2& Vector2::operator*= (Vector2 const& rhs);
		//Operators that create new Objects
		Vector2 Vector2::operator+ (Vector2 const& rhs);
		Vector2 Vector2::operator- (Vector2 const& rhs);
		Vector2 Vector2::operator* (Vector2 const& rhs);
		Vector2 Vector2::operator/ (Vector2 const& rhs);
		// Operators that change this Object
		Vector2& Vector2::operator= (float32 const& rhs);
		Vector2& Vector2::operator+= (float32 const& rhs);
		Vector2& Vector2::operator-= (float32 const& rhs);
		Vector2& Vector2::operator/= (float32 const& rhs);
		Vector2& Vector2::operator*= (float32 const& rhs);
		//Operators that create new Objects
		Vector2 Vector2::operator+ (float32 const& rhs);
		Vector2 Vector2::operator- (float32 const& rhs);
		Vector2 Vector2::operator* (float32 const& rhs);
		Vector2 Vector2::operator/ (float32 const& rhs);
	};
}