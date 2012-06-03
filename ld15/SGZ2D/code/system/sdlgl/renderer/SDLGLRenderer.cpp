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
* \file SDLGLRender.cpp
* \brief SDLGL Interface for the Renderer
*
* File Maintainer - Stuckie
*
* -----------------------------------------------------------------------------------
*/

#include "SDLGLRenderer.h"
#include "../../../arch.h"
#include "../../../common/engine/CInterpret.h"

#if defined(REND_OPENGL) || defined(REND_SDLGL)

int SDLGLRender::createRenderer ( void )
{
	/** This creates and sets up the Renderer */
	if (SDL_Init(SDL_INIT_VIDEO==-1))
	{
		Logger.log( SGZLOG::Warning, "Couldn't init SDLGL Renderer.\n");
		return -1;
	}
	else Logger.log( SGZLOG::Debug, "SDLGL Renderer initialised!\n");

	 /* Enable smooth shading */
	glShadeModel( GL_SMOOTH );

	/* Set the background black */
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	/* Depth buffer setup */
	glClearDepth( 1.0f );

	/* Enables Depth Testing */
	glEnable( GL_DEPTH_TEST );

	/* The Type Of Depth Test To Do */
	glDepthFunc( GL_LEQUAL );

	/* Really Nice Perspective Calculations */
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	Window = new SDLGLWindow;

	return 0;
}

int SDLGLRender::updateScreen( void )
{
	/** This updates the screen */
	SDL_Delay(10);
	glLoadIdentity();
//	gluLookAt(0.0,0.0,0.0,0.0,0.0,-1.0,0.0,1.0,0.0);
	Window->UpdateWindow();

	return 0;
}

int SDLGLRender::stopRenderer( void )
{
	/** This stops the Renderer */
	Window->DestroyWindow();
	Window=NULL;

	return 0;
}

int SDLGLRender::startRenderer( void )
{
	/// already started!
	return 0;
}

int SDLGLRender::createWindow( const std::string &title, const int WindowWidth, const int WindowHeight, const int WindowBPP )
{
	/** Tell the renderer to create a window */
	// We now need to create a screen ratio:
	GLfloat ratio;
	ratio = ( GLfloat )WindowWidth / ( GLfloat )WindowHeight;

	// Create the OpenGL Viewport
	glViewport( 0, 0, ( GLsizei )WindowWidth, ( GLsizei )WindowHeight );

	// Change to the Projection Matrix
	glMatrixMode( GL_PROJECTION );
	// Load the Identity Matrix to set us to 0,0,0
	glLoadIdentity( );
	// Set out Perspective up, with a LARGE viewing distance (there's method in my madness)
	gluPerspective( 45.0f, ratio, 0.1f, 2500.0f ); // should prolly cull this back a bit.. later
	// Head back to the Model Matrix
	glMatrixMode( GL_MODELVIEW );
	// And reset the view again
	glLoadIdentity( );


	return Window->createWindow(title, WindowWidth, WindowHeight, WindowBPP);
}

int SDLGLRender::closeWindow( void )
{
	/** Close The Window - We can't DO this in SDL until the end! */
	return 0;
};

int SDLGLRender::setFullScreen( const bool set )
{
	/** Setup Fullscreen mode */
	return Window->SetFullScreen(set);
}

void* SDLGLRender::getScreen( void )
{
	/** Get the screen to draw on from the Window */
	return Window->screenAccess();
}

#endif
