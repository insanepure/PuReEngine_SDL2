#include "Rect.h"

namespace PuRe 
{
	Rect::Rect()
	{
		this->Position = 0.0f;
		this->Width = 0.0f;
		this->Height = 0.0f;
	}
	Rect::Rect(float32 X,float32 Y,float32 Width,float32 Height)
	{
		this->Position = PuRe_Vector2(X,Y);
		this->Width = Width;
		this->Height = Height;
	}
	Rect::Rect(Vector2 Position,float32 Width,float32 Height)
	{
		this->Position = Position;
		this->Width = Width;
		this->Height = Height;
	}

	bool Rect::Intersects(Rect* Rectangle)
	{
		if (Rectangle->Position.X < this->Position.X + this->Width && 
			this->Position.X < Rectangle->Position.X + Rectangle->Width && 
			Rectangle->Position.Y < this->Position.Y + this->Height)

			return this->Position.Y < Rectangle->Position.Y + Rectangle->Height;
		else
			return false;
	}
	int16 Rect::IntersectSide(Rect* Rectangle)
	{
		//Abstand
		float32 PixelDist = 4.0f;
		float32 Step = 16.0f;
		float32 Start = 2.0f;
		float32 End = 12.0f;
		//Die Rectangles
		Rect Top = Rect(PuRe_Vector2(this->Position.X + this->Width / Step * Start, this->Position.Y), this->Width / Step * End, PixelDist);
		Rect Bottom = Rect(PuRe_Vector2(this->Position.X + this->Width / Step * Start, this->Position.Y + this->Height - PixelDist), this->Width / Step * End, PixelDist);
		//Abstand
		Step = 32.0f;
		Start = 2.0f;
		End = 28.0f;
		//Die Rectangle
		Rect Left = Rect(PuRe_Vector2(this->Position.X, this->Position.Y + this->Height / Step * Start), PixelDist, this->Height / Step * End);
		Rect Right = Rect(PuRe_Vector2(this->Position.X + this->Width - PixelDist, this->Position.Y + this->Height / Step * Start), PixelDist, this->Height / Step * End);
		if (Rectangle->Intersects(&Right))
			return 1;
		else if (Rectangle->Intersects(&Bottom))
			return 2;
		else if (Rectangle->Intersects(&Left))
			return 3;
		else if (Rectangle->Intersects(&Top))
			return 4;
		else
			return 0;
	}
}