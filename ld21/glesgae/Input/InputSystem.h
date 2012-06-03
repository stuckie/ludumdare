#ifndef _INPUT_SYSTEM_H_
#define _INPUT_SYSTEM_H_

#include "ControllerTypes.h"

namespace GLESGAE
{
	namespace Controller
	{
		class KeyboardController;
		class PointerController;
		class JoystickController;
		class PadController;
	}
	class CommonInputSystem
	{
		public:
			CommonInputSystem() {}
			virtual ~CommonInputSystem() {}
			
			/// Update the Input System
			virtual void update() = 0;
			
			/// Retreive number of Active Keyboards.
			virtual Controller::Id getNumberOfKeyboards() const = 0;
			
			/// Retreive number of Active Joysticks.
			virtual Controller::Id getNumberOfJoysticks() const = 0;
			
			/// Retreive number of Active Pads.
			virtual Controller::Id getNumberOfPads() const = 0;
			
			/// Retreive number of Active Pointers.
			virtual Controller::Id getNumberOfPointers() const = 0;
			
			/// Create new Keyboard - will return NULL if no more available.
			virtual Controller::KeyboardController* newKeyboard() = 0;
			
			/// Create new Joystick - will return NULL if no more available.
			virtual Controller::JoystickController* newJoystick() = 0;
			
			/// Create new Pad - will return NULL if no more available.
			virtual Controller::PadController* newPad() = 0;
			
			/// Create new Pointer - will return NULL if no more available.
			virtual Controller::PointerController* newPointer() = 0;
			
			/// Grab another instance of the specified Keyboard - returns NULL if not created.
			virtual Controller::KeyboardController* getKeyboard(const Controller::Id id) = 0;
			
			/// Grab another instance of the specified Joystick - returns NULL if not created.
			virtual Controller::JoystickController* getJoystick(const Controller::Id id) = 0;
			
			/// Grab another instance of the specified Pointer - returns NULL if not created.
			virtual Controller::PointerController* getPointer(const Controller::Id id) = 0;
			
			/// Grab another instance of the specified Pad - returns NULL if not created.
			virtual Controller::PadController* getPad(const Controller::Id id) = 0;
			
			/// Destroy a Keyboard.
			virtual void destroyKeyboard(Controller::KeyboardController* const keyboard) = 0;
			
			/// Destroy a Joystick.
			virtual void destroyJoystick(Controller::JoystickController* const joystick) = 0;
			
			/// Destroy a Pad.
			virtual void destroyPad(Controller::PadController* const pad) = 0;
			
			/// Destroy a Pointer.
			virtual void destroyPointer(Controller::PointerController* const pointer) = 0;
	};
}

#if defined(PANDORA)
	#include "Pandora/PandoraInputSystem.h"
#elif defined(LINUX)
	#include "Linux/LinuxInputSystem.h"
#endif

#endif
