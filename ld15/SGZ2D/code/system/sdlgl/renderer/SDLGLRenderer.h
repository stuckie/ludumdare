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

#ifndef _SDLGLRENDERER_H_
#define _SDLGLRENDERER_H_

#include "../../../arch.h"

#if defined (REND_SDLGL)

#include "IRender.h"
#include "SDLGLWindow.h"
#include "CDebug.h"

#include "GL/gl.h"
#include "GL/glu.h"
#include "SDL/SDL.h"

class SDLGLRender : public IRender
{
	public:
	 SDLGLRender() {};
	~SDLGLRender() {};

	int CreateRenderer ( void );
	/** This creates and sets up the Renderer */

	int StartRenderer( void );
	/** Starts the renderer */

	int UpdateScreen( void );
	/** This updates the screen */

	int StopRenderer( void );
	/** This stops the Renderer */

	int SGZCreateWindow( std::string title, int WindowWidth, int WindowHeight, int WindowBPP );
	/** Creates a Window */

	int SGZCloseWindow( void );
	/** Closes a Window */

	int SetFullScreen( bool set );
	/** Toggles fullscreen ( for those that support it ) */

	void* GetScreen( void );
	/** Returns the current Window Screen to draw */

	int TakeScreenshot ( void ) { return 0; };

	private:
	SDLGLWindow *Window;
};

#endif

#endif
