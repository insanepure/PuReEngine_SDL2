#pragma once
#include <vector>
#ifdef __linux__
//LINUX
#include <SDL2/SDL.h>
#elif _WIN32
//Windows
#include <SDL.h>
#include <SDL_mixer.h>
#elif _APPLE_
#include "TargetConditionals.h"
#ifdef TARGET_OS_MAC
//MAC
#endif
#endif

#include "Defines.h"

namespace PuRe
{
	class Audio
	{
	public:
		Audio();
		~Audio();
		void AddSound(const char* file);
		void AddMusic(const char* file);
		void SetVolume(int16 Volume,int16 channel);
		void SetVolumeMusic(int16 Volume);
		void Play(int16 times,int16 channel);
		void PauseMusic();
		void PlayMusic(int16 times,int16 channel);
		void Pause(int16 channel);
	private:
		PuRe_List<Mix_Music*> musics;
		PuRe_List<Mix_Chunk*> samples;
		bool can;
	};
}