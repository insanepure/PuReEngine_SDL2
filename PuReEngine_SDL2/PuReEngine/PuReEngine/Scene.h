#pragma once
#include "Graphics.h"
namespace PuRe {
	struct Scene
	{
		virtual void Initialize(Graphics* graphics) = 0;

		virtual bool Update(float timeMultiplicator,Graphics* graphics) = 0;

		virtual void Render(Graphics* graphics) = 0;

		virtual void Exit() = 0;
	};

}
