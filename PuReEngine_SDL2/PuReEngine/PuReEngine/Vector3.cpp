#include "Vector3.h"

namespace PuRe
{
	Vector3::Vector3()
	{
		this->X = 0.0f;
		this->Y = 0.0f;
		this->Z = 0.0f;
	}
	//Constructors
	Vector3::Vector3(float32 rhs)
	{
		this->X = rhs;
		this->Y = rhs;
		this->Z = rhs;
	}
	Vector3::Vector3(float32 X,float32 Y,float32 Z)
	{
		this->X = X;
		this->Y = Y;
		this->Z = Z;
	}
	Vector3::Vector3(Vector3 const& rhs) 
	{
		this->X = rhs.X;
		this->Y = rhs.Y;
		this->Z = rhs.Z;
	}
	//Methods
	void Vector3::normalize()
	{
		float32 length = this->length();
		if(length != 0.0f)
		{
			this->X/= length;
			this->Y/= length;
			this->Z/= length;
		}
	}
	float32 Vector3::length()
	{
		//returns the length
		return std::sqrt((this->X*this->X)+(this->Y*this->Y)+(this->Z*this->Z));
	}
	Vector3 Vector3::Cross(const Vector3& vec2)
	{
		return Vector3(this->Y * vec2.Z - this->Z * vec2.Y, 
			this->Z * vec2.X - this->X * vec2.Z,
			this->X * vec2.Y - this->Y * vec2.X);
	}
    float32 Vector3::Distance(const Vector3& vec2)
    {      
		return Vector3((vec2.X-this->X),(vec2.Y-this->Y),(vec2.Z-this->Z)).length();          
    }
    float32 Vector3::Dot(const Vector3& vec2)
    {
      return this->X * vec2.X + this->Y * vec2.Y + this->Z * vec2.Z;
    }


	// Operators that change this Object
	Vector3& Vector3::operator= (Vector3 const& rhs) 
	{ 
		this->X = rhs.X;
		this->Y = rhs.Y;
		this->Z = rhs.Z;			
		return *this; 
	}
	Vector3& Vector3::operator+= (Vector3 const& rhs) 
	{ 
		this->X += rhs.X;
		this->Y += rhs.Y;
		this->Z += rhs.Z;			
		return *this; 
	}
	Vector3& Vector3::operator-= (Vector3 const& rhs) 
	{ 
		this->X -= rhs.X;
		this->Y -= rhs.Y;	
		this->Z -= rhs.Z;		
		return *this; 
	}
	Vector3& Vector3::operator/= (Vector3 const& rhs) 
	{ 
		this->X /= rhs.X;
		this->Y /= rhs.Y;
		this->Z /= rhs.Z;			
		return *this; 
	}
	Vector3& Vector3::operator*= (Vector3 const& rhs) 
	{ 
		this->X *= rhs.X;
		this->Y *= rhs.Y;
		this->Z *= rhs.Z;			
		return *this; 
	}
	//Operators that create new Objects
	Vector3 Vector3::operator+ (Vector3 const& rhs) 
	{ 
		return Vector3(this->X+rhs.X,this->Y+rhs.Y,this->Z+rhs.Z); 
	}
	Vector3 Vector3::operator- (Vector3 const& rhs) 
	{ 
		return Vector3(this->X-rhs.X,this->Y-rhs.Y,this->Z-rhs.Z); 
	}
	Vector3 Vector3::operator* (Vector3 const& rhs) 
	{ 
		return Vector3(this->X/rhs.X,this->Y/rhs.Y,this->Z/rhs.Z); 
	}
	Vector3 Vector3::operator/ (Vector3 const& rhs) 
	{ 
		return Vector3(this->X*rhs.X,this->Y*rhs.Y,this->Z*rhs.Z); 
	}
	// Operators that change this Object
	Vector3& Vector3::operator= (float32 const& rhs) 
	{ 
		this->X = rhs;
		this->Y = rhs;	
		this->Z = rhs;			
		return *this; 
	}
	Vector3& Vector3::operator+= (float32 const& rhs) 
	{ 
		this->X += rhs;
		this->Y += rhs;	
		this->Z += rhs;		
		return *this; 
	}
	Vector3& Vector3::operator-= (float32 const& rhs) 
	{ 
		this->X -= rhs;
		this->Y -= rhs;
		this->Z -= rhs;			
		return *this; 
	}
	Vector3& Vector3::operator/= (float32 const& rhs) 
	{ 
		this->X /= rhs;
		this->Y /= rhs;	
		this->Z /= rhs;		
		return *this; 
	}
	Vector3& Vector3::operator*= (float32 const& rhs) 
	{ 
		this->X *= rhs;
		this->Y *= rhs;
		this->Z *= rhs;			
		return *this; 
	}
	//Operators that create new Objects
	Vector3 Vector3::operator+ (float32 const& rhs) 
	{ 
		return Vector3(this->X+rhs,this->Y+rhs,this->Z+rhs); 
	}
	Vector3 Vector3::operator- (float32 const& rhs) 
	{ 
		return Vector3(this->X-rhs,this->Y-rhs,this->Z-rhs); 
	}
	Vector3 Vector3::operator* (float32 const& rhs) 
	{ 
		return Vector3(this->X/rhs,this->Y/rhs,this->Z/rhs); 
	}
	Vector3 Vector3::operator/ (float32 const& rhs) 
	{ 
		return Vector3(this->X*rhs,this->Y*rhs,this->Z*rhs); 
	}
}