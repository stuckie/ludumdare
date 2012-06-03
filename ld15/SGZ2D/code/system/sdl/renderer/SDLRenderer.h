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
	\file SDLRender.h
	\brief SDL Interface for the Renderer
*/

#ifndef _SDLRENDERER_H_
#define _SDLRENDERER_H_

// Include any needed Interfaces
#include "../../../client/renderer/IRender.h"
#include "../../../client/renderer/window/IWindow.h"

// Include the SDL Header
#include "SDL/SDL.h"

class SDLRender : public SGZ::IRender
{

	private:
	SGZ::IWindow *mWindow;

	public:
		SDLRender()
		: mWindow(NULL)
		{
			/*nope*/
		};

		SDLRender( const SDLRender& )
		: mWindow(NULL)
		{
		}

		SDLRender operator=( const SDLRender& )
		{
			return *this;
		}

		~SDLRender()
		{
			/*nope*/
		};

		int createRenderer ( void );
		/* This creates and sets up the Renderer */

		int startRenderer ( void );
		/* Starts the Renderer */

		int updateScreen( void );
		/* This updates the screen */

		int stopRenderer( void );
		/* This stops the Renderer */

		int createWindow( const std::string &pTitle, const int pWindowWidth, const int pWindowHeight, const int pWindowBPP );
		/* We create a window to play with */

		int closeWindow( void );
		/* Closes The Window */

		int setFullscreen( const bool pSet );
		/* Set Fullscreen mode */

		void* getScreen( void );

		int takeScreenshot( void );

}; // End of SDLRender

#endif
