#include "Timer.h"

#include <SDL/SDL.h>

Timer::Timer()
: currentTime_(SDL_GetTicks())
{
	
}

const float Timer::processDelta()
{
	float newTime(SDL_GetTicks());
	const float delta(newTime - currentTime_);
	currentTime_ = newTime;
	
	return delta / 1000.0F;
}
