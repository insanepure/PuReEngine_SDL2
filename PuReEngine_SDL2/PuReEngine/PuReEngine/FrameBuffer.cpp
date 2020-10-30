#include "FrameBuffer.h"

namespace PuRe
{
	FrameBuffer::FrameBuffer(PuRe_Texture* Texture)
	{
		gFBO = 0;
		glGenFramebuffers(1, &gFBO);
		this->Texture = Texture;
	}
	void FrameBuffer::Bind()
	{
        glBindFramebuffer( GL_FRAMEBUFFER, gFBO );
        glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->Texture->GetID(), 0 );
		glClear( GL_COLOR_BUFFER_BIT );
	}
	void FrameBuffer::UnBind()
	{
        glBindFramebuffer( GL_FRAMEBUFFER, NULL );
	}
	FrameBuffer::~FrameBuffer()
	{

	}
}
