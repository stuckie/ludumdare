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
* \file SDLWindow.cpp
* \brief SDL Interface for launching a Window
*
* File Maintainer - Stuckie
*
* -----------------------------------------------------------------------------------
*/

#include "SDLWindow.h"
#include "../../../common/engine/CInterpret.h"
#include "../../../common/debug/CDebug.h"
#include <ctime>

int SDLWindow::createWindow( const std::string &title, const int WindowWidth, const int WindowHeight, const int WindowBPP )
{
	/** This creates a window with the title named. */

	/// Creating Window
	mScreen = SDL_SetVideoMode(WindowWidth, WindowHeight, WindowBPP, SDL_SWSURFACE);// | SDL_DOUBLEBUF);
	if(!mScreen)
	{
		SGZ::Logger.log( SGZLOG::Warning, "Could not create SDL Screen.\n");
		return -1;
	}

	/// Set the Window Title
	SDL_WM_SetCaption(title.c_str(),title.c_str());

	/// Setup the Back Buffer Rect
	mBackBuffer.x=0;
	mBackBuffer.y=0;
	mBackBuffer.w=WindowWidth;
	mBackBuffer.h=WindowHeight;

	mScreenshot = false;

	return 0;
}

int SDLWindow::destroyWindow( void )
{
	/** This destroys the window. */
	mScreen = NULL;
	return 0;
}

void* SDLWindow::screenAccess( void )
{
	/** Returns the surface to the Window */
	return mScreen;
}

bool SDLWindow::takeScreenshot( void )
{
	mScreenshot = true;
	return true;
}

bool SDLWindow::updateWindow( void )
{
	if(mScreen)
	{
		if(mScreenshot)
		{
			char screenshotName[64];
			sprintf(screenshotName, "screenshot%d.bmp", (int)time(NULL));
			SDL_SaveBMP(mScreen, screenshotName);
			mScreenshot = false;
		}
		SDL_Flip(mScreen);
		SDL_FillRect(mScreen, &mBackBuffer, 0);
		return true;
	}
	else
		return false;

}

int SDLWindow::setFullScreen( bool set )
{
	if(set)
		mScreen = SDL_SetVideoMode(mScreen->w, mScreen->h, mScreen->format->BitsPerPixel, SDL_ANYFORMAT|SDL_DOUBLEBUF|SDL_FULLSCREEN);
	else
		mScreen = SDL_SetVideoMode(mScreen->w, mScreen->h, mScreen->format->BitsPerPixel, SDL_ANYFORMAT|SDL_DOUBLEBUF);

	return 0;
}
