#ifndef _QUIRKS_LIFE_CYCLE_H_
#define _QUIRKS_LIFE_CYCLE_H_

#include <Platform/Lifecycle.h>
#include <Resources/Resource.h>
#include <Events/EventObserver.h>

namespace GLESGAE {
	class EventSystem;
	class InputSystem;
	class GraphicsSystem;
	class StateStack;
	class Clock;
	class Timer;
}

class QuirksLifecycle : public GLESGAE::Lifecycle, public GLESGAE::EventObserver
{
	public:
		QuirksLifecycle();
		~QuirksLifecycle();

		/// Receive any System Events we may have registered interest in
		void receiveEvent(const GLESGAE::Resource<GLESGAE::Event>& event);

		/// onCreate - Called by the platform as soon as the application is started - IE: To setup Platform specifics.
		void onCreate();
		
		/// onStart - Called by the platform once it's initialized - IE: Platform specifics have been setup.
		void onStart();
		
		/// onResume - Called by the platform when our application has came back from a Paused state.
		void onResume();
		
		/// onLoop - Called by the platform to generate a new frame of logic.
		bool onLoop();
		
		/// onPause - Called by the platform before our application must enter a paused state.
		void onPause();
		
		/// onStop - Called by the platform before our application must enter a stopped state.
		void onStop();
		
		/// onDestroy - Called by the platform before our application is stopped - IE: to save state, etc...
		void onDestroy();

#if defined(PANDORA)
	#include "Pandora/QuirksLifecycle.h"
#elif defined(LINUX)
	#include "Linux/QuirksLifecycle.h"
#elif defined(WIN32)
	#include "Win32/QuirksLifecycle.h"
#elif defined(DARWIN)
	#include "Darwin/QuirksLifecycle.h"
#elif defined(IOS)
	#include "iOS/QuirksLifecycle.h"
#elif defined(ANDROID)
	#include "Android/QuirksLifecycle.h"
#endif

	private:
		GLESGAE::Resource<GLESGAE::EventSystem> mEventSystem;
		GLESGAE::Resource<GLESGAE::InputSystem> mInputSystem;
		GLESGAE::Resource<GLESGAE::GraphicsSystem> mGraphicsSystem;
		GLESGAE::Resource<GLESGAE::StateStack> mStateStack;
		GLESGAE::Resource<GLESGAE::Clock> mClock;
		GLESGAE::Resource<GLESGAE::Timer> mMainTimer;
};

#endif

