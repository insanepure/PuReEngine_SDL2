#include "Vector2.h"

namespace PuRe
{
	Vector2::Vector2()
	{
		this->X = 0.0f;
		this->Y = 0.0f;
	}
	//Constructors
	Vector2::Vector2(float32 rhs)
	{
		this->X = rhs;
		this->Y = rhs;
	}
	Vector2::Vector2(float32 X,float32 Y)
	{
		this->X = X;
		this->Y = Y;
	}
	Vector2::Vector2(Vector2 const& rhs) 
	{
		this->X = rhs.X;
		this->Y = rhs.Y;
	}
	//Methods
	void Vector2::normalize()
	{
		float32 length = this->length();
		if(length != 0.0f)
		{
			this->X/= length;
			this->Y/= length;
		}
	}
	float32 Vector2::length()
	{
		//returns the length
		return std::sqrt((this->X*this->X)+(this->Y*this->Y));
	}
    float32 Vector2::Distance(const Vector2& vec2)
    {      
		return Vector2((vec2.X-this->X),(vec2.Y-this->Y)).length();          
    }
    float32 Vector2::Dot(const Vector2& vec2)
    {
      return this->X * vec2.X + this->Y * vec2.Y;
    }


	// Operators that change this Object
	Vector2& Vector2::operator= (Vector2 const& rhs) 
	{ 
		this->X = rhs.X;
		this->Y = rhs.Y;		
		return *this; 
	}
	Vector2& Vector2::operator+= (Vector2 const& rhs) 
	{ 
		this->X += rhs.X;
		this->Y += rhs.Y;		
		return *this; 
	}
	Vector2& Vector2::operator-= (Vector2 const& rhs) 
	{ 
		this->X -= rhs.X;
		this->Y -= rhs.Y;		
		return *this; 
	}
	Vector2& Vector2::operator/= (Vector2 const& rhs) 
	{ 
		this->X /= rhs.X;
		this->Y /= rhs.Y;		
		return *this; 
	}
	Vector2& Vector2::operator*= (Vector2 const& rhs) 
	{ 
		this->X *= rhs.X;
		this->Y *= rhs.Y;		
		return *this; 
	}
	//Operators that create new Objects
	Vector2 Vector2::operator+ (Vector2 const& rhs) 
	{ 
		return Vector2(this->X+rhs.X,this->Y+rhs.Y); 
	}
	Vector2 Vector2::operator- (Vector2 const& rhs) 
	{ 
		return Vector2(this->X-rhs.X,this->Y-rhs.Y); 
	}
	Vector2 Vector2::operator* (Vector2 const& rhs) 
	{ 
		return Vector2(this->X/rhs.X,this->Y/rhs.Y); 
	}
	Vector2 Vector2::operator/ (Vector2 const& rhs) 
	{ 
		return Vector2(this->X*rhs.X,this->Y*rhs.Y); 
	}
	// Operators that change this Object
	Vector2& Vector2::operator= (float32 const& rhs) 
	{ 
		this->X = rhs;
		this->Y = rhs;		
		return *this; 
	}
	Vector2& Vector2::operator+= (float32 const& rhs) 
	{ 
		this->X += rhs;
		this->Y += rhs;		
		return *this; 
	}
	Vector2& Vector2::operator-= (float32 const& rhs) 
	{ 
		this->X -= rhs;
		this->Y -= rhs;		
		return *this; 
	}
	Vector2& Vector2::operator/= (float32 const& rhs) 
	{ 
		this->X /= rhs;
		this->Y /= rhs;		
		return *this; 
	}
	Vector2& Vector2::operator*= (float32 const& rhs) 
	{ 
		this->X *= rhs;
		this->Y *= rhs;		
		return *this; 
	}
	//Operators that create new Objects
	Vector2 Vector2::operator+ (float32 const& rhs) 
	{ 
		return Vector2(this->X+rhs,this->Y+rhs); 
	}
	Vector2 Vector2::operator- (float32 const& rhs) 
	{ 
		return Vector2(this->X-rhs,this->Y-rhs); 
	}
	Vector2 Vector2::operator* (float32 const& rhs) 
	{ 
		return Vector2(this->X/rhs,this->Y/rhs); 
	}
	Vector2 Vector2::operator/ (float32 const& rhs) 
	{ 
		return Vector2(this->X*rhs,this->Y*rhs); 
	}
}