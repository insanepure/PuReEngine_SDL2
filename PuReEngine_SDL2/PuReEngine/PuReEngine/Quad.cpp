#include "Quad.h"

namespace PuRe
{
	Quad::Quad()
	{
		this->gVBO = 0;
		this->gIBO = 0;
		//VertexPositionen des Quads in Modelspace
		GLfloat vertexData[] =
		{
			-1.0f, -1.0f, 0.0f,
			 1.0f, -1.0f ,0.0f,
			 1.0f,  1.0f ,0.0f,
			-1.0f,  1.0f, 0.0f
		};
		
		GLfloat UVData[] =
		{
			-1.0f, -1.0f,
			 1.0f, -1.0f,
			 1.0f,  1.0f,
			-1.0f,  1.0f
		};

		//Indexdaten
		GLuint indexData[] = { 0, 1, 2, 3 };

		//Erzeuge UV Buffer Object
		glGenBuffers( 1, &this->gUVBO );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->gUVBO );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, 2 * 4 * sizeof(GLuint), UVData, GL_STATIC_DRAW );

		//Erzeuge Vertex Buffer Object
		glGenBuffers( 1, &this->gVBO );
		glBindBuffer( GL_ARRAY_BUFFER, this->gVBO );
		glBufferData( GL_ARRAY_BUFFER, 3 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW );

		//Erzeuge Index Buffer Object
		glGenBuffers( 1, &this->gIBO );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->gIBO );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW );
	}
	void Quad::Draw(Rect DRect,bool flip,float32 Width,float32 Height,PuRe_Material* Mat)
	{

		//Definiere die UV Werte
		float32 UV_X = DRect.Position.X/Width;
		float32 UV_Y = DRect.Position.Y/Height;
		float32 UV_SIZE_X = DRect.Width/Width;
		float32 UV_SIZE_Y = DRect.Height/Height;

		//Falls er sich spiegeln soll
		if(flip)
		{
			UV_X = UV_X+UV_SIZE_X;
			UV_SIZE_X = -UV_SIZE_X;
		}
		//Packe die UV Werte zusammen
		GLfloat UVData[] =
		{
			 UV_X, UV_Y,
			 UV_X+UV_SIZE_X, UV_Y,
			 UV_X+UV_SIZE_X, UV_Y+UV_SIZE_Y,
			 UV_X, UV_Y+UV_SIZE_Y
		};
		////////////// VERTEX BUFFER  BENUTZEN ///////////////
		glBindBuffer(GL_ARRAY_BUFFER, this->gVBO);
		Mat->BindPosition();

		////////////// UV BUFFER  BENUTZEN ///////////////
		glBindBuffer(GL_ARRAY_BUFFER, this->gUVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(UVData), UVData, GL_STATIC_DRAW);
		Mat->BindUV();
		//Aktiviere den Index Buffer
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->gIBO );

		/////////// ZEICHNEN /////////////
		glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, 0 );

	}
	Quad::~Quad()
	{
		glDeleteBuffers(1, &this->gVBO);
		glDeleteBuffers(1, &this->gIBO);
		glDeleteBuffers(1, &this->gUVBO);
	}
}