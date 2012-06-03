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
	\file IWindow.h
	\brief The Window Interface

*/

#ifndef _IWINDOW_H_
#define _IWINDOW_H_

#include <string>

namespace SGZ
{
	class IWindow
	{
		public:
			virtual ~IWindow() {}

			virtual int createWindow( const std::string &pTitle, const int pWindowWidth, const int pWindowHeight, const int pWindowBPP ) = 0;
			/** This creates a window with the title named. */

			virtual int destroyWindow( void ) = 0;
			/** This destroys the window number defined. */

			virtual bool updateWindow( void ) = 0;
			/** Tell us to update the window */

			virtual int setFullScreen( const bool pSet ) = 0;
			/** Setup Fullscreen mode */

			virtual bool takeScreenshot( void ) = 0;
			/** Takes a screenshot */

	}; // End of IWindow

} // End of Namespace

#endif // End of _IWINDOW_H_
