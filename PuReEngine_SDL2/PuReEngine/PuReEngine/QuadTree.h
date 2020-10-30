#pragma once
#include "Defines.h"
#include "Rect.h"
#include <vector>
namespace PuRe
{
	class QuadTree
	{
	private:
		int16 level;
		PuRe_List<PuRe_Rect*> objects;

		int16 MaxLevel;
		uint16 MaxObjects;
		Rect Bounds;
		QuadTree* nodes[4];

		int16 getNode(Rect* Object)
		{
			//gehe die Notes durch und guck wo das object sich drin befindet
			for(int16 i=0;i<4;i++)
			{
				if(Object->Intersects(&this->nodes[i]->Bounds))
				{
					return i;
					break;
				}
			}
			return -1;
		}

		void Split()
		{
			//Erzeuge die vier Bereiche
			PuRe_Rect NewBound = PuRe_Rect(this->Bounds.Position.X,this->Bounds.Position.Y,this->Bounds.Width/2,this->Bounds.Height/2);
			this->nodes[0] = new PuRe_QuadTree(this->level+1,NewBound);
			NewBound.Position.X += this->Bounds.Width/2;
			this->nodes[1] = new PuRe_QuadTree(this->level+1,NewBound);
			NewBound.Position.Y += this->Bounds.Height/2;
			this->nodes[2] = new PuRe_QuadTree(this->level+1,NewBound);
			NewBound.Position.X -= this->Bounds.Width/2;
			this->nodes[3] = new PuRe_QuadTree(this->level+1,NewBound);
			//Gehe die Elemente durch
			for(uint16 i=0;i<objects.size();i++)
			{
				int index = this->getNode(objects[i]); //In was für ein Node es sich befindet
				if(index != -1)
					this->nodes[index]->Insert(objects[i]); //Füge es dort hinzu
			}
			//Lere die Elementenliste
			this->objects.clear(); 
		}
	public:
		~QuadTree()
		{
			this->Clear();
		}
		void Draw(PuRe_Sprite* Sprite,PuRe_Material* Mat)
		{
			if(nodes[0] == nullptr)
			{
				PuRe_Vector3 SpritePos(this->Bounds.Position.X,this->Bounds.Position.Y,0.0f);
				PuRe_Vector3 Scale(this->Bounds.Width,this->Bounds.Height,1.0f);
				PuRe_Vector3 Origin(0.0f,0.0f,1.0f);
				PuRe_Vector3 Color(0.0f,0.0f,0.0f);
				PuRe_Rect Rect(0.0f,0.0f,16.0f,16.0f);
				Sprite->Draw(SpritePos,Scale,Origin,0.0f,Color,Rect,false,Mat);
			}
			else
			{

				PuRe_Vector3 SpritePos(this->Bounds.Position.X,this->Bounds.Position.Y,0.0f);
				PuRe_Vector3 Scale(this->Bounds.Width,this->Bounds.Height,1.0f);
				PuRe_Vector3 Origin(0.0f,0.0f,1.0f);
				PuRe_Vector3 Color(0.0f,0.0f,0.0f);
				PuRe_Rect Rect(0.0f,0.0f,16.0f,16.0f);
				Sprite->Draw(SpritePos,Scale,Origin,0.0f,Color,Rect,false,Mat);
				for(int16 i=0;i<4;i++)
				{
					this->nodes[i]->Draw(Sprite,Mat);
				}
			}
		}
		QuadTree(int16 level,Rect Bounds)
		{
			this->level = level;
			this->Bounds = Bounds;
			this->MaxLevel = 5;
			this->MaxObjects = 2;
			for (int16 i = 0; i < 4; i++) 
			{
				nodes[i] = nullptr;
			}
		}

		void Clear()
		{
			this->objects.clear();
			for (int16 i = 0; i < 4; i++) 
			{
				if (nodes[i] != nullptr) 
				{
					delete nodes[i];
					nodes[i] = nullptr;
				}
			}
		}
		//Füge ein
		void Insert(Rect* Object)
		{
			if(nodes[0] == nullptr)
			{
				//Hat sich noch nicht aufgeteilt
				objects.push_back(Object);
				if(objects.size() > this->MaxObjects&&this->level < this->MaxLevel)
				{
					//Aufsplitten
					Split();
				}
			}
			else
			{
				int index = getNode(Object);
				if(index != -1)
					this->nodes[index]->Insert(Object);
			}
		}
		PuRe_List<Rect*> GetCollide(Rect* Object)
		{
			if(nodes[0] == nullptr)
			{
				return this->objects;
			}
			else
			{
				int index = getNode(Object);
				if(index != -1)
					return this->nodes[index]->GetCollide(Object); //returnt rekursiv
				else
				{
					PuRe_List<PuRe_Rect*> newList;
					return newList;
				}
			}
		}
	};
}