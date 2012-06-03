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

#ifndef _SDLGLWINDOW_H_
#define _SDLGLWINDOW_H_

#include "../../../arch.h"
#include "../../../client/renderer/window/IWindow.h"
#include "../../../common/engine/OEvent.h"
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

class SDLGLWindow : public IWindow
{
	private:

	SDL_Surface *mScreen;	//!< Pointer to our Screen
	SDL_Rect mBackBuffer;	//!< Our Back Buffer
	SDL_Event mEvent;		//!< For checking Window Events

	bool mScreenshot;

	public:
	SDLGLWindow()
	: mScreen(0)
	{
		/* nope */
	}

	SDLGLWindow operator=( const SDLGLWindow& )
	{
		throw("not implemented");
	}

	SDLGLWindow( const SDLGLWindow& )
	{
		throw ("not implemented");
	}

	~SDLGLWindow() {
		/* nope */
	}

	int createWindow( const std::string &title, const int pWindowWidth, const int pWindowHeight, const int pWindowBPP );
	/** This creates a window with the title named. */

	int destroyWindow( void );
	/** This destroys the window. */

	bool updateWindow( void );
	/** Update the Window */

	int setFullScreen( const bool set );
	/** Setup Fullscreen Mode */

	void* screenAccess( void );
	/** Returns the surface to the Window */

	bool takeScreenshot( void );

};


#endif
