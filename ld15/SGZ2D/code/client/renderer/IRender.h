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
	\file IRender.h
	\brief The Interface for the Renderer
*/

#ifndef _IRENDER_H_
#define _IRENDER_H_

#include <string>

namespace SGZ
{
	class IRender
	{
		public:
			virtual ~IRender()
			{
				/* nope */
			}

			virtual int createRenderer ( void ) = 0;
			/* This creates and sets up the Renderer */

			virtual int updateScreen( void ) = 0;
			/* This updates the screen */

			virtual int takeScreenshot( void ) = 0;
			/* Takes a screenshot */

			virtual int stopRenderer( void ) = 0;
			/* This stops the Renderer */

			virtual int startRenderer( void ) = 0;
			/* This starts the Renderer */

			virtual int createWindow( const std::string &pTitle, const int pWindowWidth, const int pWindowHeight, const int pWindowBPP ) = 0;
			/* Creates a Window */

			virtual int closeWindow( void ) = 0;
			/* Closes a Window */

			virtual int setFullscreen( const bool pSet ) = 0;
			/* Toggles fullscreen ( for those that support it ) */

			virtual void* getScreen( void ) = 0;
			/* Returns the current Window Screen to draw */

	}; // End of IRender

} // End of Namespace

#endif

/** Changelog for this file:
*/
