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

#include "../../../arch.h"

#ifndef _HORDERENDER_H_
#define _HORDERENDER_H_

	#if defined(REND_HORDE) || defined(REND_SDLHORDE)

	#include "../../../client/renderer/IRender.h"
	#include "../../../client/renderer/window/IWindow.h"

	class HordeRender : public SGZ::IRender
	{
		private:

			/// Renderer objects
			SGZ::IWindow *mWindow;

		public:
			HordeRender();
			~HordeRender();

			int createRenderer ( void );
			/** This creates and sets up the Renderer */

			int updateScreen( void );
			/** This updates the screen */

			int takeScreenshot( void );
			/** Takes a screenshot */

			int stopRenderer( void );
			/** This stops the Renderer */

			int createWindow( const std::string &pTitle, const int pWindowWidth, const int pWindowHeight, const int pWindowBPP );
			/** Creates a Window */

			int closeWindow( void );
			/** Closes a Window */

			int setFullscreen( const bool set );
			/** Toggles fullscreen ( for those that support it ) */

			void* getScreen( void );
			/** Returns the current Window Screen to draw */

			int startRenderer( void );
			/** Start up the Renderer */

	};

	#endif // End of SDLHorde | Horde check

#endif // End of HORDERENDER_H_
