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
 \file SDLTexture.h
 \brief The SDL Interface for Textures
*/

#ifndef _SDLTEXTURE_H_
#define _SDLTEXTURE_H_

#include "../../../arch.h"
#include "../../../client/renderer/texture/ITexture.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class SDLTexture : public SGZ::ITexture
{
	private:
		SDL_Surface *mTexture;
		SGZ::RGBCOLOUR mTexCol, mColKey;
		SDL_Rect mOffset;

	public:
		SDLTexture()
		:   mTexture(),
			mTexCol(),
			mColKey(),
			mOffset()
		{
		}

		SDLTexture( const SDLTexture& )
		:   mTexture(),
			mTexCol(),
			mColKey(),
			mOffset()
		{
		}

		SDLTexture operator=(const SDLTexture& )
		{
			throw("");
		}

		~SDLTexture()
		{
		}

		bool createTexture ( void );
		/** This creates and sets up a blank texture, which we sometimes need, and gets it ready to load one in if we want. */

		bool loadTexture ( const std::string &Filename );
		/** This loads in a texture */

		bool setColour( const SGZ::RGBCOLOUR &colour );
		bool blitTexture( const SGZ::VECTOR3 &vector, const SGZ::SCALER u, const SGZ::SCALER v, const SGZ::SCALER w, const SGZ::SCALER h);
		bool blitTexture(		   float , float , float , float ,
									float , float , float , float ,
									float , float , float , float ,
									float , float , float , float ,
									int  )
									{ return true; }

		bool setColourKey( const SGZ::RGBCOLOUR &colkey );
		/** Sets the colour key -- transparancy */

		void* getTexture( void );
		/** This returns the texture, which since it could be anything, is a void pointer */

		void* getTextureMask ( void ) {return NULL;};
		bool loadTextureMask ( const std::string& ) { return true;};

		bool deleteTexture( void );
		/** Deletes the memory used by this texture */

};

#endif
