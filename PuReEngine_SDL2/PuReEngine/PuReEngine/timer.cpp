#include "Timer.h"
#include <stdio.h>

namespace PuRe
{
	Timer::Timer()
	{
		this->timeStepMs = 1000 / 60;
		this->timeLastMs  = 0;
		this->timeCurrentMs = 0;
		this->timeDeltaMs  = 0;
		this->timeAccumulatedMs  = 0;
	}
	Timer::~Timer()
	{
	}

	void Timer::Update()
	{
		//Speichert den Zeitpunkt des letzten Updates auf das aktuelle
		this->timeLastMs = this->timeCurrentMs;
		//Holt die Aktuelle Zeit
		this->timeCurrentMs = SDL_GetTicks();
		//Berechnet die Differenz zwischen dem letzten und den jetzigen Update
		this->timeDeltaMs = this->timeCurrentMs - this->timeLastMs;
		////Addiert die Differenz
		//this->timeAccumulatedMs += this->timeDeltaMs;
		//Wenn die Addition der Differenzen größer ist als 60Hz
		this->timeMultiplicator = this->timeDeltaMs/1000.0f;
		//if(timeAccumulatedMs >= timeStepMs)
		//{
		//	//Return true für Update und setzte minus
		//	this->timeAccumulatedMs -= this->timeStepMs;
		//	return true;
		//}
		//else
		//	return false;
	}
}