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
	\file OTexture.h
	\brief The Texture Object

*/

#ifndef _OTEXTURE_H_
#define _OTEXTURE_H_

#include "ITexture.h"

#ifdef REND_SDL
#include "../../../system/sdl/renderer/SDLTexture.h"
#endif

#ifdef REND_SDLGL
#include "../../../system/sdlgl/renderer/SDLGLTexture.h"
#endif

#ifdef REND_OPENGL
#include "../../../system/opengl/GLTexture.h"
#endif

#if defined(REND_OGRE) || defined(REND_SDLOGRE)
#include "../../../system/ogre/OGRETexture.h"
#endif

#if defined(REND_HORDE) || defined(REND_SDLHORDE)
#include "../../../system/horde/renderer/HordeTexture.h"
#endif

class OTexture : SGZ::ITexture
{
	private:
	#ifdef REND_SDL
		SDLTexture	   mTexture;
	#endif
	#ifdef REND_SDLGL
		SDLGLTexture	 mTexture;
	#endif
	#ifdef REND_OPENGL
		GLTexture		mTexture;
	#endif
	#if defined(REND_OGRE) || defined(REND_SDLOGRE)
		OGRETexture	 mTexture;
	#endif
	#if defined(REND_HORDE) || defined(REND_SDLHORDE)
		HordeTexture	mTexture;
	#endif

	public:
	OTexture()
	: mTexture()
	{
		createTexture();
	};

	~OTexture()
	{
		deleteTexture();
	};

	bool createTexture ( void ) {
		return mTexture.createTexture();
	}
	/** This creates and sets up a blank texture, which we sometimes need, and gets it ready to load one in if we want. */

	bool loadTexture ( const std::string &pFilename ) {
		return mTexture.loadTexture( pFilename );
	}
	/** This loads in a texture */

	bool loadTextureMask ( const std::string &pFilename ) {
		return mTexture.loadTextureMask( pFilename );
	}
	/** This loads in a texture */

	void* getTexture( void ) {
		return mTexture.getTexture();
	}
	/** This returns the texture, which since it could be anything, is a void pointer */

	void* getTextureMask( void ) {
		return mTexture.getTextureMask();
	}
	/** This returns the texture mask, which since it could be anything, is a void pointer */

	bool deleteTexture( void ) {
		return mTexture.deleteTexture();
	}
	/** Deletes the memory used by this texture */

	bool setColourKey( const SGZ::RGBCOLOUR &pColkey ) {
		return mTexture.setColourKey( pColkey );
	}
	/** Sets transparency */

	bool blitTexture( const SGZ::VECTOR3 &vector, const SGZ::SCALER u, const SGZ::SCALER v, const SGZ::SCALER w, const SGZ::SCALER h ) {
		return mTexture.blitTexture( vector, u, v, w, h );
	}
	/** Blits straight to screen */

	bool blitTexture(	const float x1, const float y1, const float u1, const float v1,
								const float x2, const float y2, const float u2, const float v2,
								const float x3, const float y3, const float u3, const float v3,
								const float x4, const float y4, const float u4, const float v4,
																				const int layer ) {
		return mTexture.blitTexture(	x1, y1, u1, v1,
										x2, y2, u2, v2,
										x3, y3, u3, v3,
										x4, y4, u4, v4,
												layer );
	}
	/** Blits the Horde Way - top corner XY, top corner UV to bottom corner XY, bottome corner UV*/

	bool setColour( const SGZ::RGBCOLOUR &pColour ) {
		return mTexture.setColour( pColour );
	}
	/** Sets the Colour */


};

#endif
