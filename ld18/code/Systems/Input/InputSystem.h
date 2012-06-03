#ifndef _INPUT_SYSTEM_H_
#define _INPUT_SYSTEM_H_

#include <SDL/SDL.h>

class InputSystem
{
	public:
		~InputSystem();
	
		//! Creates or returns the current active instance.
		static InputSystem& instance();
		
		void initialise();
		void update();
		const bool hasQuit() const;
		
		const bool keyDown(const SDLKey key) const { return keyboardBuffer_[key]; }
		
	private:
		InputSystem();
		
		static InputSystem* instance_;	//!< Active instance
		Uint8* keyboardBuffer_;
};

#endif
