#include "Sprite.h"

namespace PuRe
{
	Sprite::Sprite(PuRe_Quad* Quad,PuRe_Texture* Texture)
	{
		this->Quad = Quad;
		this->Texture = Texture;
	}
	void Sprite::Draw(PuRe_Vector3 Position,PuRe_Vector3 Scale,PuRe_Vector3 Origin,float32 Angle,PuRe_Vector3 Color,Rect DRect,bool flip,PuRe_Material* Material)
	{
		glm::vec3 gOrigin = glm::vec3(Origin.X, Origin.Y, Origin.Z);

		glm::mat4 RotationMatrix =  glm::translate(glm::mat4(), gOrigin) * 
									glm::mat4_cast(glm::quat(glm::vec3(0,0,Angle))) * 
									glm::translate(glm::mat4(), -gOrigin);
		
		glm::mat4 TranslationMatrix = glm::translate(glm::mat4(), glm::vec3(Position.X+Scale.X/2, Position.Y+Scale.Y/2, Position.Z+Scale.Z/2));

		glm::mat4 ScalingMatrix = glm::scale(glm::mat4(), glm::vec3(Scale.X/2, Scale.Y/2, Scale.Z/2));
		

		Material->setModel(RotationMatrix*TranslationMatrix*ScalingMatrix);

		Material->setColor(glm::vec4(Color.X,Color.Y,Color.Z,1.0f));

        glUniformMatrix4fv(this->ModelID, 1, GL_FALSE, glm::value_ptr(this->Model));
        glUniformMatrix4fv(this->ViewID, 1, GL_FALSE, glm::value_ptr(this->View));
        glUniformMatrix4fv(this->ProjectionID, 1, GL_FALSE, glm::value_ptr(this->Projection));
        glUniform4f(this->ColorID, this->Color.r, this->Color.g, this->Color.b, this->Color.a);
        glUniform1i(this->TextureID, 0);
        glUniform1f(this->TimeID, this->Time);
        glUniform2f(this->ResolutionID, this->Resolution.X, this->Resolution.Y);
		Material->Update();

        glActiveTexture(GL_TEXTURE0);
        //Binde die Textur mit OpenGL
        glBindTexture(GL_TEXTURE_2D, this->TextureID);
        this->Texture->Bind();
        ////////////// VERTEX BUFFER  BENUTZEN ///////////////
        glBindBuffer(GL_ARRAY_BUFFER, this->gVBO);
        Mat->BindPosition();

        ////////////// UV BUFFER  BENUTZEN ///////////////
        glBindBuffer(GL_ARRAY_BUFFER, this->gUVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(UVData), UVData, GL_STATIC_DRAW);
        Mat->BindUV();
        //Aktiviere den Index Buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->gIBO);

        /////////// ZEICHNEN /////////////
        glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, 0);
		this->Quad->Draw(DRect,flip,(float32)this->Texture->GetWidth(),(float32)this->Texture->GetHeight(),Material);
		this->Texture->UnBind();
	}
	Sprite::~Sprite()
	{
	}
}