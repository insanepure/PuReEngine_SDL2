#include "Audio.h"

namespace PuRe
{
	Audio::Audio()
	{
		this->can = true;

		Mix_Init(MIX_INIT_MP3);
		if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) 
		{
			printf("Mix_OpenAudio: %s\n", Mix_GetError());
			this->can = false;
		}
		Mix_AllocateChannels(100);

	}
	void Audio::AddSound(const char* file)
	{
		if(this->can)
		{
			this->samples.push_back(Mix_LoadWAV(file));
			if(!this->samples[this->samples.size()-1]) 
			{
				printf("Mix_LoadMUS Sound: %s\n", Mix_GetError());
				// handle error
			}
		}
	}
	void Audio::AddMusic(const char* file)
	{
		if(this->can)
		{
			this->musics.push_back(Mix_LoadMUS(file));
			if(!this->musics[this->musics.size()-1]) 
			{
				printf("Mix_LoadMUS Music: %s\n", Mix_GetError());
			}
		}
	}
	void Audio::SetVolumeMusic(int16 Volume)
	{
		if(this->can)
		{
			Mix_VolumeMusic(Volume);
		}
	}
	void Audio::SetVolume(int16 Volume,int16 channel)
	{
		if(this->can)
		{
			Mix_VolumeChunk(this->samples[channel], Volume);
		}
	}
	void Audio::PauseMusic()
	{
		if(this->can)
		{
			Mix_PauseMusic();
		}
	}
	void Audio::Pause(int16 channel)
	{
		if(this->can)
		{
			Mix_Pause(channel);
		}
	}
	void Audio::Play(int16 times,int16 channel)
	{
		if(this->can)
		{
			int c = Mix_PlayChannel(channel, this->samples[channel], times);
			if(c==-1) 
			{
				printf("Mix_PlayChannel: %s\n",Mix_GetError());
			}
			else
				printf("Play Sound #%i on Channel #%i\n",channel,c);
		}
	}
	void Audio::PlayMusic(int16 times,int16 channel)
	{
		if(this->can)
		{
			Mix_PlayMusic(this->musics[channel],times);
		}
	}
	Audio::~Audio()
	{
		if(this->can)
		{
			for(uint16 i=0;i<this->samples.size();i++)
			{
				Mix_FreeChunk(this->samples[i] ); 
			}
			for(uint16 i=0;i<this->musics.size();i++)
			{
				Mix_FreeMusic(this->musics[i] ); 
			}
		}
		Mix_CloseAudio();
	}
}