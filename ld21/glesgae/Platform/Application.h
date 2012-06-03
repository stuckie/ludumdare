#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "../Graphics/GraphicsSystem.h"

namespace GLESGAE
{
	class EventSystem;
	class InputSystem;
	class ResourceManager;
	class Lifecycle;
	class StateStack;
	class Clock;	
	class Application
	{
		public:
			~Application() {}
			
			/// Application is a Singleton and can only be accessed via this method.
			static Application* getInstance();
			
			/// Set the user lifecycle
			void setLifecycle(Lifecycle* const lifecycle);
			
			// Lifecycle Bits
			/// onCreate - Called by the platform as soon as the application is started - IE: To setup Platform specifics.
			void onCreate(const GraphicsSystem::RenderType renderType);
			
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
			
			// Retrieve Systems
			/// Retrieve the Input System
			InputSystem* getInputSystem() const { return mInputSystem; }
			
			/// Retrieve the Event System
			EventSystem* getEventSystem() const { return mEventSystem; }
			
			/// Retrieve the Graphics System
			GraphicsSystem* getGraphicsSystem() const { return mGraphicsSystem; }
			
			/// Retrieve the Resource Manager
			ResourceManager* getResourceManager() const { return mResourceManager; }
			
			/// Retrieve the State Stack
			StateStack* getStateStack() const { return mStateStack; }
			
			/// Retrieve the System Clock
			Clock* getClock() const { return mClock; }
			
		private:
			/// Private constructor as this can only be created and managed through it's singleton.
			Application();
			/// No copying
			Application(const Application&);
			/// No equals operator
			Application& operator=(const Application&);
			
			static Application* mInstance;
			
			EventSystem* mEventSystem;
			GraphicsSystem* mGraphicsSystem;
			InputSystem* mInputSystem;
			ResourceManager* mResourceManager;
			Lifecycle* mLifecycle;
			StateStack* mStateStack;
			Clock* mClock;
	};
}

#endif

