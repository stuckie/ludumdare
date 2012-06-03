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
	\file HordeRender.cpp
	\brief Horde's Render Layer

*/

#include "HordeRender.h"
#if defined(REND_SDLHORDE) || defined(REND_HORDE)

#include "../../sdlgl/window/SDLGLWindow.h"

#include "Horde3D.h"
#include "Horde3DUtils.h"

#include "../../../common/debug/CDebug.h"

using namespace SGZ;

HordeRender::HordeRender()
{

}

HordeRender::~HordeRender()
{
	Horde3D::release();
}

int HordeRender::createRenderer ( void )
{
	/** This creates and sets up the Renderer */


	if (SDL_Init(SDL_INIT_VIDEO==-1))
	{
		Logger.log( SGZLOG::Warning, "Couldn't init SDL.\n");
		return -1;
	}
	else Logger.log( SGZLOG::Debug, "SDL initialised!\n");

	SDL_ShowCursor(SDL_DISABLE); // Not that SDL seems to take much notice of this!

	mWindow = new SDLGLWindow;

	return 0;
}

int HordeRender::updateScreen( void )
{
	/** This updates the screen and dumps Horde's debug messages at the same time */
	Horde3DUtils::dumpMessages();

	mWindow->updateWindow();

	return 0;
}

int HordeRender::startRenderer( void )
{
	return 0;
}

int HordeRender::takeScreenshot( void )
{
	/** Takes a screenshot */
	return mWindow->takeScreenshot();
}

int HordeRender::stopRenderer( void )
{
	/** This stops the Renderer */
	Horde3DUtils::dumpMessages();
	mWindow->destroyWindow();

	return 0;
}

int HordeRender::createWindow( const std::string &pTitle, const int pWindowWidth, const int pWindowHeight, const int pWindowBPP )
{
	/** Creates a Window */
	Horde3D::resize(0,0,pWindowWidth,pWindowHeight);
	return mWindow->createWindow( pTitle, pWindowWidth, pWindowHeight, pWindowBPP);
}

int HordeRender::closeWindow( void )
{
	/** Closes a Window */
	return mWindow->destroyWindow();
}

int HordeRender::setFullscreen( const bool pSet )
{
	/** Toggles fullscreen ( for those that support it ) */
	return mWindow->setFullScreen( pSet );
}

void* HordeRender::getScreen( void )
{
	/** Returns the current Window Screen to draw.. but Horde does this itself */

	return NULL;
}

#endif
