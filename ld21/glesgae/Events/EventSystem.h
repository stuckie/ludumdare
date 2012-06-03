#ifndef _EVENT_SYSTEM_H_
#define _EVENT_SYSTEM_H_

#include "EventTypes.h"
// This defines general purpose Event System logic.
// Each of the platform specific headers ( included below ) extend this.

#include <map>
#include <vector>

namespace GLESGAE
{
	class Event;
	class EventObserver;
	class EventTrigger;
	class RenderWindow;
	class CommonEventSystem
	{
		public:
			CommonEventSystem()
			: mEventObservers()
			, mEventTriggers()
			{

			}

			virtual ~CommonEventSystem() {}

			/// Update the Event System.
			virtual void update() = 0;

			/// Bind to specified Window.
			virtual void bindToWindow(RenderWindow* const window) = 0;

			/// Register an Event Type.
			void registerEventType(const EventType& eventType);

			/// Register an Event Observer with Event Type.
			void registerObserver(const EventType& eventType, EventObserver* const observer);

			/// Deregister an Event Observer from Event Type.
			void deregisterObserver(const EventType& eventType, EventObserver* const observer);

			/// Register a Custom Event Trigger.
			void registerEventTrigger(const EventType& eventType, EventTrigger* const trigger);

			/// Deregister a Custom Event Trigger.
			void deregisterEventTrigger(const EventType& eventType, EventTrigger* const trigger);

			/// Send an Event to all Observers of this type.
			/// If you want to retain this event beyond it being in the receiving scope, you'll have to copy it.
			void sendEvent(const EventType& eventType, Event* event);

		protected:
			/// Update all the Triggers to send Events if necessary.
			void updateAllTriggers();

			std::map<EventType, std::vector<EventObserver*> > mEventObservers; 	//!< Outer = Event Type; Inner = Array of Event Observers for this Event Type. These are callback pointers, so no need to delete them.
			std::map<EventType, std::vector<EventTrigger*> > mEventTriggers;	//!< Outer = Event Type; Inner = Array of Event Triggers for this Event Type. These are callback pointers, so no need to delete them.
	};
}

#if defined(LINUX)
	#include "X11/X11EventSystem.h"
#endif

#endif
