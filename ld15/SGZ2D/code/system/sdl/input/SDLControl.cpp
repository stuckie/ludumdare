/*
	SGZEngine
	Copyright (C) 2008 - 2009 Steven Campbell

	This engine is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This engine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this engine; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

	Steven Campbell
	stuckie@stuckiegamez.co.uk
*/

/**
	\file SDLControl.cpp
	\brief The SDL Controller Object
*/

#include "SDLControl.h"
#include <cstdlib>
#include "../../../client/OClient.h"
#include "../../../common/engine/CInterpret.h"

bool SDLControl::createInterface(void)
{
	/* Create a control interface to talk on */
	mMouseX=0,mMouseY=0;
	SDL_EnableUNICODE( SDL_ENABLE );
	mLastKey = "";
	#ifndef PLAT_A320
		SDL_Init(SDL_INIT_JOYSTICK);
		mJoypad1 = SDL_JoystickOpen(0);
		mJoypad2 = SDL_JoystickOpen(1);
	#endif
	SDL_WM_GrabInput(SDL_GRAB_ON);
	SDL_ShowCursor(0);

	return true;
}

bool SDLControl::destroyInterface(void)
{
	/** Destroy a control interface */
	SDL_EnableUNICODE( SDL_DISABLE );
	SDL_Quit();
	return true;
}

bool SDLControl::updateControls(void)
{
	/** Update The Controls if there's an event waiting for us! */
	if(SDL_PollEvent(&mEvent)) {
		/** Check to see if we've quit */
		if(mEvent.type==SDL_QUIT) {
			atexit(SDL_Quit);
			SGZ::Interpret.quit();
		}


		/** Check the keyboard */
		if (mEvent.type==SDL_KEYUP) {
			mButtons[mEvent.key.keysym.sym]=0;
			mLastKey = "";
		}
		if (mEvent.type==SDL_KEYDOWN) {
			mButtons[mEvent.key.keysym.sym]=1;
			mLastKey += (char)mEvent.key.keysym.sym;
		}

		if(mButtons[SDLK_ESCAPE]) {
			SGZ::Interpret.quit();;
		}

		/** Check the mouse */
		if (mEvent.type==SDL_MOUSEBUTTONDOWN) {
			mMouseX=mEvent.button.x;
			mMouseY=mEvent.button.y;
			SGZ::Interpret.accessClient()->updateMouseButtons(true, (int)mEvent.button.button);
			SGZ::Interpret.accessClient()->updateMousePos(mMouseX, mMouseY);
		}

		if (mEvent.type==SDL_MOUSEBUTTONUP) {
			mMouseX=mEvent.button.x;
			mMouseY=mEvent.button.y;
			SGZ::Interpret.accessClient()->updateMouseButtons(false, (int)mEvent.button.button);
			SGZ::Interpret.accessClient()->updateMousePos(mMouseX, mMouseY);
		}

		if (mEvent.type==SDL_MOUSEMOTION)
			if(mMouseX!=mEvent.motion.x && mMouseY!=mEvent.motion.y) {
				mMouseX=mEvent.motion.x;
				mMouseY=mEvent.motion.y;
				SGZ::Interpret.accessClient()->updateMousePos(mMouseX, mMouseY);
			}
	}

	#ifndef PLAT_A320
		SDL_JoystickUpdate();
	#endif

	return true;
}
