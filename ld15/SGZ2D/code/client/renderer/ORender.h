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
	\file ORender.h
	\brief The Renderer Object
*/

#ifndef _ORENDER_H_
#define _ORENDER_H_

#include "IRender.h"

/*  Don't you just love the cross-platform multi-platform goodness?
	Here we go with a large complicated whack of system renderers!
	There is no doubt a FAR better way to do this...			  */

#ifdef REND_SDL
	#include "../../system/sdl/renderer/SDLRenderer.h"
#endif
#ifdef REND_SDLGL
	#include "../../system/sdlgl/renderer/SDLGLRenderer.h"
#endif
#ifdef REND_OPENGL
	#include "../../system/opengl/GLRenderer.h"
#endif
#ifdef REND_DIRECTX
	#include "../../system/directx/renderer/DXRenderer.h"
#endif
#ifdef REND_WINAPI
	#include "../../system/winapi/renderer/WINRenderer.h"
#endif
#ifdef REND_SPS2
	#include "../../system/ps2linux/renderer/SPS2Renderer.h"
#endif
#if defined(REND_SDLOGRE) || defined(REND_OGRE)
	#include "../../system/ogre/renderer/OGRERenderer.h"
#endif
#if defined(REND_HORDE) || defined(REND_SDLHORDE)
	#include "../../system/horde/renderer/HordeRender.h"
#endif

class ORender : public SGZ::IRender
{
	private:

		#ifdef REND_SDL
			SDLRender	mRenderer;
		#endif
		#ifdef REND_SDLGL
			SDLGLRender	mRenderer;
		#endif
		#ifdef REND_OPENGL
			GLRender	mRenderer;
		#endif
		#ifdef REND_DIRECTX
			DXRender	mRenderer;
		#endif
		#ifdef REND_WINAPI
			WINRender	mRenderer;
		#endif
		#ifdef REND_SPS2
			SPS2Render	mRenderer;
		#endif
		#if defined(REND_OGRE) || defined(REND_SDLOGRE)
			OGRERender	mRenderer;
		#endif
		#if defined(REND_HORDE) || defined(REND_SDLHORDE)
			HordeRender	mRenderer;
		#endif

	public:

		ORender()
		:   mRenderer()
		{
			/* nope */
		}

		~ORender()
		{
			/* nope */
		}

		int createRenderer ()
			{ return mRenderer.createRenderer(); }

		int updateScreen()
			{ return mRenderer.updateScreen(); }

		int stopRenderer( void )
			{ return mRenderer.stopRenderer(); }

		int startRenderer()
			{ return mRenderer.startRenderer(); }

		int createWindow( const std::string &pTitle, const int pWindowWidth, const int pWindowHeight, const int pWindowBPP )
			{ return mRenderer.createWindow( pTitle, pWindowWidth, pWindowHeight, pWindowBPP ); }

		int closeWindow()
			{ return mRenderer.closeWindow(); }

		int setFullscreen( const bool pSet )
			{ return mRenderer.setFullscreen( pSet ); }

		void* getScreen()
			{ return mRenderer.getScreen(); }

		int takeScreenshot ()
			{ return mRenderer.takeScreenshot(); }

}; // End of ORender

#endif
