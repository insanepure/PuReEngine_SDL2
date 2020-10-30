#pragma once
#include "Defines.h"
#include <cmath>
namespace PuRe 
{
	class Vector3
	{
	public:
		//Variables
		float32 X,Y,Z;
		//Standard Constructor
		Vector3();
		//Constructors
		Vector3(float32 rhs);
		Vector3(float32 X,float32 Y,float32 Z);
		Vector3(Vector3 const& rhs);
		//Methods
		void normalize();
		float32 length();
		float32 Dot(const Vector3& vec2);
		Vector3 Cross(const Vector3& vec2);
		float32 Distance(const Vector3& vec2);
		// Operators that change this Object
		Vector3& Vector3::operator= (Vector3 const& rhs);
		Vector3& Vector3::operator+= (Vector3 const& rhs);
		Vector3& Vector3::operator-= (Vector3 const& rhs);
		Vector3& Vector3::operator/= (Vector3 const& rhs);
		Vector3& Vector3::operator*= (Vector3 const& rhs);
		//Operators that create new Objects
		Vector3 Vector3::operator+ (Vector3 const& rhs);
		Vector3 Vector3::operator- (Vector3 const& rhs);
		Vector3 Vector3::operator* (Vector3 const& rhs);
		Vector3 Vector3::operator/ (Vector3 const& rhs);
		// Operators that change this Object
		Vector3& Vector3::operator= (float32 const& rhs);
		Vector3& Vector3::operator+= (float32 const& rhs);
		Vector3& Vector3::operator-= (float32 const& rhs);
		Vector3& Vector3::operator/= (float32 const& rhs);
		Vector3& Vector3::operator*= (float32 const& rhs);
		//Operators that create new Objects
		Vector3 Vector3::operator+ (float32 const& rhs);
		Vector3 Vector3::operator- (float32 const& rhs);
		Vector3 Vector3::operator* (float32 const& rhs);
		Vector3 Vector3::operator/ (float32 const& rhs);
	};
}