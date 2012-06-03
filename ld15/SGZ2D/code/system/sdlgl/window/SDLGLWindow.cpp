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

/** --------------------------------------------------------------------------------
* \file SDLGLWindow.cpp
* \brief SDLGL Interface for launching a Window
*
* File Maintainer - Stuckie
*
* -----------------------------------------------------------------------------------
*/

#include "SDLGLWindow.h"
#include "../../../common/engine/CInterpret.h"

int SDLGLWindow::createWindow( const std::string &title, const int WindowWidth, const int WindowHeight, const int WindowBPP )
{
	/** This creates a window with the title named. */

	/// Creating Window
	mScreen = SDL_SetVideoMode(WindowWidth, WindowHeight, WindowBPP, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE | SDL_HWSURFACE | SDL_HWACCEL);
	if(!mScreen)
	{
		Logger.log( SGZLOG::Warning, "Could not create SDL Screen.\n");
		return -1;
	}
	Logger.log( SGZLOG::Debug, "SDLWindow Created\n");

	/// Set the Window Title
	SDL_WM_SetCaption(title.c_str(),title.c_str());

	/// Set Double Buffering on for GL
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	mScreenshot = false;

	return 0;
}

int SDLGLWindow::destroyWindow( void )
{
	/** This destroys the window. */
	mScreen = NULL;
	return 0;
}

void* SDLGLWindow::screenAccess( void )
{
	/** Returns the surface to the Window */
	return mScreen;
}

bool SDLGLWindow::updateWindow( void )
{
	if(mScreen)
	{
		SDL_GL_SwapBuffers();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		return true;
	}
	else
		return false;

}

bool SDLGLWindow::takeScreenshot( void )
{
	mScreenshot = true;
	return true;
}

int SDLGLWindow::setFullScreen( const bool set )
{
	if(set)
		mScreen = SDL_SetVideoMode(mScreen->w, mScreen->h, mScreen->format->BitsPerPixel, SDL_FULLSCREEN | SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE | SDL_HWSURFACE | SDL_HWACCEL);
	else
		mScreen = SDL_SetVideoMode(mScreen->w, mScreen->h, mScreen->format->BitsPerPixel, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE | SDL_HWSURFACE | SDL_HWACCEL);

	return 0;
}

