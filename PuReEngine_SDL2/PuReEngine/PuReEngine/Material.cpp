#include "Material.h"

namespace PuRe
{
	Material::Material( const char* vertex_path,const char* fragment_path )
	{
		this->VertexUV = -2;
		this->VertexPosition = -1;
		this->Time = 0.0f;
		this->programID = NULL;
		//Erzeuge das Programm
		this->programID = glCreateProgram();
		//Lade den Vertex Shader
		this->vertexID = this->loadShader(vertex_path,GL_VERTEX_SHADER);
		//Attach Vertex und Program
		glAttachShader( this->programID, this->vertexID );
		//Erzeuge Fragment
		this->fragmentID = this->loadShader(fragment_path,GL_FRAGMENT_SHADER);
		//Attach Fragment und Program
		glAttachShader( this->programID, this->fragmentID );
		//Link program
		glLinkProgram( this->programID );

		//Überprüfe ob Fehler da sind
		GLint programSuccess = GL_TRUE;
		glGetProgramiv( this->programID, GL_LINK_STATUS, &programSuccess );
		if( programSuccess != GL_TRUE )
		{
			//Es gab fehler
			printf( "Error linking program %d!\n", this->programID );
			this->ProgramLog( this->programID );
			glDeleteProgram( this->programID );
			this->programID = 0;
		}
		//Füge Variablen dazu
		this->VertexUV = glGetAttribLocation( this->programID, "vertexUV" );
		this->VertexPosition = glGetAttribLocation( this->programID, "VertexPosition" );
		this->TimeID  = glGetUniformLocation(this->programID, "Time");
		this->TextureID  = glGetUniformLocation(this->programID, "myTextureSampler");
		this->ColorID = glGetUniformLocation( this->programID, "Color" );
		this->ModelID = glGetUniformLocation( this->programID, "Model" );
		this->ViewID = glGetUniformLocation( this->programID, "View" );
		this->ProjectionID = glGetUniformLocation( this->programID, "Projection" );
	}
	void Material::setTime(float32 Time)
	{
		this->Time = Time;
	}
	//Definiere MVP extern
	void Material::setModel(glm::mat4 Model)
	{
		this->Model = Model;
	}
	void Material::setView(glm::mat4 View)
	{
		this->View = View;
	}
	void Material::setProjection(glm::mat4 Projection)
	{
		this->Projection = Projection;
	}
	void Material::setColor(glm::vec4 Color)
	{
		this->Color = Color;
	}
	void Material::setResolution(PuRe_Vector2 Resolution)
	{
		this->Resolution = Resolution;
	}
	void Material::Update()
	{
		//Benutzt die MVP Matrizen in dem Shader
		glUniformMatrix4fv(	this->ModelID, 1, GL_FALSE, glm::value_ptr( this->Model ) );
		glUniformMatrix4fv(	this->ViewID, 1, GL_FALSE, glm::value_ptr( this->View ) );
		glUniformMatrix4fv(	this->ProjectionID, 1, GL_FALSE, glm::value_ptr( this->Projection ) );
		glUniform4f( this->ColorID, this->Color.r, this->Color.g, this->Color.b, this->Color.a );
		glUniform1i(this->TextureID, 0);
		glUniform1f(this->TimeID,this->Time);
		glUniform2f(this->ResolutionID,this->Resolution.X,this->Resolution.Y);
	}
	void Material::BindPosition()
	{
		glEnableVertexAttribArray( this->VertexPosition );
		glVertexAttribPointer( this->VertexPosition, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL );
	}
	void Material::BindUV()
	{
		glEnableVertexAttribArray( this->VertexUV );
		glVertexAttribPointer( this->VertexUV, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL );
	}
	void Material::Bind()
	{
		//Use shader
		glUseProgram( this->programID );
	}
	void Material::UnBind()
	{
		//Höre auf die VertexPosition zu nutzen
		glDisableVertexAttribArray( this->VertexPosition );
		//Höre auf die VertexUV zu nutzen
		glDisableVertexAttribArray( this->VertexUV );
		//Unbind program
		glUseProgram( NULL );
	}

	//Intern
	GLuint Material::loadShader(const char* path,GLenum shaderType)
	{
		GLuint shader = 0;
		//Variablen
		std::string shaderString;
		//Öffne Datei
		std::ifstream sourceFile( path );
		//Datei geöffnet
		if( sourceFile )
		{
			//Lese alles heraus
			shaderString.assign( ( std::istreambuf_iterator< char >( sourceFile ) ), std::istreambuf_iterator< char >() );
			//Erzeuge Shader je nach Typ
			shader = glCreateShader( shaderType );
			//Setze den Code
			const GLchar* shaderSource = shaderString.c_str();
			glShaderSource( shader, 1, (const GLchar**)&shaderSource, NULL );
			//Kompiliere den Code
			glCompileShader( shader );
			//Überprüfe nach Fehlern
			GLint shaderCompiled = GL_FALSE;
			glGetShaderiv( shader, GL_COMPILE_STATUS, &shaderCompiled );
			if( shaderCompiled != GL_TRUE )
			{
				//Fehler
				printf( "Unable to compile shader %d!\n\nSource:\n%s\n", shader, shaderSource );
				this->ShaderLog( shader );
				glDeleteShader( shader );
				shader = 0;
			}
		}
		else
		{
			printf( "Unable to open file %s\n", path );
		}
		return shader;
	}
	void Material::ProgramLog(GLuint program)
	{
		//Wenn program existiert
		if( glIsProgram( program ) )
		{
			//Programm länge
			int infoLogLength = 0;
			int maxLength = infoLogLength;

			//Hole die Länge des Fehlers
			glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );

			//Allocate string
			char* infoLog = new char[ maxLength ];

			//Hole den Fehler
			glGetProgramInfoLog( program, maxLength, &infoLogLength, infoLog );
			if( infoLogLength > 0 )
			{
				//Printe den Fehler
				printf( "%s\n", infoLog );
			}

			//Deallocate string
			delete[] infoLog;
		}
		else
		{
			printf( "Name %d is not a program\n", program );
		}
	}
	void Material::ShaderLog(GLuint shader)
	{
		//Wenn es ein Shader ist
		if( glIsShader( shader ) )
		{
			//Log Länge
			int infoLogLength = 0;
			int maxLength = infoLogLength;
			
			//Hole die Länge des Fehlers
			glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );

			//Allocate string
			char* infoLog = new char[ maxLength ];
			
			//Hole den Fehler
			glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog );
			if( infoLogLength > 0 )
			{
				//Printe den Fehler
				printf( "%s\n", infoLog );
			}

			//Deallocate string
			delete[] infoLog;
		}
		else
		{
			printf( "Name %d is not a shader\n", shader );
		}
	}
	Material::~Material()
	{
		glDeleteProgram( this->programID );
		glUseProgram( NULL );
	}
}