#include "Texture.h"

namespace PuRe
{
	Texture::Texture()
	{
		this->TextureID = 0;
	}
	void Texture::LoadDDS(const char* path)
	{
		//lade das Bild
		unsigned char header[124];

		FILE *fp;
		/* try to open the file */
		fp = fopen(path, "rb");
		if (fp == NULL){
			printf("%s Datei kann nicht gefunden werden !\n", path); getchar();
		}

		/* verify the type of file */
		char filecode[4];
		fread(filecode, 1, 4, fp);

		/* get the surface desc */
		fread(&header, 124, 1, fp);

		unsigned int height      = *(unsigned int*)&(header[8 ]);
		unsigned int width	     = *(unsigned int*)&(header[12]);
		unsigned int linearSize	 = *(unsigned int*)&(header[16]);
		unsigned int mipMapCount = *(unsigned int*)&(header[24]);
		unsigned int fourCC      = *(unsigned int*)&(header[80]);

		this->Height = height;
		this->Width = width;


		unsigned char * buffer;
		unsigned int bufsize;
		/* how big is it going to be including all mipmaps? */
		bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
		buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
		fread(buffer, 1, bufsize, fp);
		/* close the file pointer */
		fclose(fp);

		unsigned int format;
		switch(fourCC)
		{
		case FOURCC_DXT1:
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			break;
		case FOURCC_DXT3:
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			break;
		case FOURCC_DXT5:
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			break;
		default:
			free(buffer);
			printf("Falsches DXT Format bei %s\n",path);
		}

		// Create one OpenGL texture
		glGenTextures(1, &this->TextureID);

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, this->TextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R,GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glPixelStorei(GL_UNPACK_ALIGNMENT,1);

		unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
		unsigned int offset = 0;

		/* load the mipmaps */
		for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
		{
			unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
			glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
				0, size, buffer + offset);

			offset += size;
			width  /= 2;
			height /= 2;

			// Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
			if(width < 1) width = 1;
			if(height < 1) height = 1;

		}

		free(buffer);
	}
	GLuint Texture::GetID()
	{
		return this->TextureID;
	}
	void Texture::Empty(float Width,float Height)
	{
        glGenTextures( 1, &this->TextureID );

        //Bind texture ID
        glBindTexture( GL_TEXTURE_2D, this->TextureID );

        //Generate texture
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)Width, (GLsizei)Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );

        //Set texture parameters
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

        //Unbind texture
        glBindTexture( GL_TEXTURE_2D, NULL );
	}
	void Texture::Bind()
	{
		glActiveTexture(GL_TEXTURE0);
		//Binde die Textur mit OpenGL
		glBindTexture(GL_TEXTURE_2D, this->TextureID);
	}
	void Texture::UnBind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);  
	}
	uint16 Texture::GetWidth()
	{
		return this->Width;
	}
	uint16 Texture::GetHeight()
	{
		return this->Height;
	}
	Texture::~Texture()
	{
		glDeleteTextures(1,&this->TextureID);
	}
}