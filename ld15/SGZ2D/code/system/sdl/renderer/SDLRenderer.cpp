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
	\file SDLRender.cpp
	\brief SDL Interface for the Renderer
*/

#include "SDLRenderer.h"
#include "../../../common/debug/CDebug.h"
#include "../window/SDLWindow.h"
#include "../../../common/engine/CInterpret.h"

using namespace SGZ;

int SDLRender::createRenderer ( void )
{
	/** This creates and sets up the Renderer */
	if (SDL_Init(SDL_INIT_VIDEO==-1))
	{
		Logger.log( SGZLOG::Warning, "Couldn't init SDL Renderer.\n");
		return -1;
	}
	else Logger.log( SGZLOG::Debug, "SDL Renderer initialised!\n");

	mWindow = new SDLWindow;

	return 0;
}

int SDLRender::updateScreen( void )
{
	/** This updates the screen */
	SDL_Delay(1);
	mWindow->updateWindow();
	return 0;
}

int SDLRender::stopRenderer( void )
{
	/** This stops the Renderer */
	mWindow->destroyWindow();
	mWindow=NULL;

	return 0;
}

int SDLRender::startRenderer( void )
{
	/// already started!
	return 0;
}

int SDLRender::createWindow( const std::string &pTitle, const int pWindowWidth, const int pWindowHeight, const int pWindowBPP )
{
	/** Tell the renderer to create a window */
	return mWindow->createWindow( pTitle, pWindowWidth, pWindowHeight, pWindowBPP);
}

int SDLRender::closeWindow( void )
{
	/** Close The Window - We can't DO this in SDL until the end! */
	return 0;
}

int SDLRender::setFullscreen( const bool pSet )
{
	/** Setup Fullscreen mode */
	return mWindow->setFullScreen( pSet );
}

void* SDLRender::getScreen( void )
{
	/** Get the screen to draw on from the Window */
	return static_cast<SDLWindow*>(mWindow)->screenAccess();
}

int SDLRender::takeScreenshot( void )
{
	return mWindow->takeScreenshot();
}
