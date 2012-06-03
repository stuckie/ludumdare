#ifndef _AUDIO_SYSTEM_H_
#define _AUDIO_SYSTEM_H_

class AudioSystem
{
	public:
		~AudioSystem();
	
		//! Creates or returns the current active instance.
		static AudioSystem& instance();
		
	private:
		AudioSystem();

		static AudioSystem* instance_;	//!< Active instance
};

#endif
