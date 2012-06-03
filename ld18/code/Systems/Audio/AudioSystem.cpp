#include "AudioSystem.h"

AudioSystem* AudioSystem::instance_ = 0;

AudioSystem& AudioSystem::instance()
{
	if (0 == instance_)
		instance_ = new AudioSystem;
		
	return *instance_;		
}

AudioSystem::AudioSystem()
{
	
}

AudioSystem::~AudioSystem()
{
	delete instance_;
	instance_ = 0;
}
