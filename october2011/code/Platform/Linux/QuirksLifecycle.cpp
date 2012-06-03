#include "../QuirksLifecycle.h"

#include <Platform/Application.h>
#include <Events/EventSystem.h>
#include <Events/SystemEvents.h>
#include <Input/InputSystem.h>
#include <Graphics/GraphicsSystem.h>
#include <Graphics/Renderer/GLES10/FixedFunctionGlVARenderer.h>
#include <Time/Clock.h>
#include <Time/Timer.h>

#include "../../States/Intro/IntroState.h"

using namespace GLESGAE;

QuirksLifecycle::QuirksLifecycle()
: mEventSystem()
, mInputSystem()
, mGraphicsSystem()
, mStateStack()
, mClock()
, mMainTimer(new Timer)
{
}

QuirksLifecycle::~QuirksLifecycle()
{
}

void QuirksLifecycle::receiveEvent(const Resource<Event>& event)
{
	if (event->getEventType() == SystemEvents::Window::Closed)
		mStateStack->pop();
}

void QuirksLifecycle::onCreate()
{
	Application* application(Application::getInstance());
	mGraphicsSystem = application->getGraphicsSystem();
	
	mGraphicsSystem->initialise("Little Quirks", 640, 480, 24, false);
	mGraphicsSystem->getCurrentContext()->setRenderer(Resource<Renderer>(new FixedFunctionGlVARenderer));
	
	mEventSystem = application->getEventSystem();
	mEventSystem->bindToWindow(mGraphicsSystem->getCurrentWindow());
	mEventSystem->registerObserver(SystemEvents::Window::Closed, this);
	
	mClock = application->getClock();
	mInputSystem = application->getInputSystem();
	mStateStack = application->getStateStack();
}

void QuirksLifecycle::onStart()
{
	mClock->reset();
	mMainTimer->reset();
	mStateStack->push<IntroState>();
}

void QuirksLifecycle::onResume()
{
}

bool QuirksLifecycle::onLoop()
{
	mMainTimer->update(mClock);

	mEventSystem->update();
	mInputSystem->update();

	return mStateStack->update(mMainTimer->getDelta());
}

void QuirksLifecycle::onPause()
{
}

void QuirksLifecycle::onStop()
{
}

void QuirksLifecycle::onDestroy()
{
}

