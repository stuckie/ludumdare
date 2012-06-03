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
* \file SDLTexture.cpp
* \brief The SDL Interface for Textures
*
* File Maintainer - Stuckie
*
* -----------------------------------------------------------------------------------
*/

#include "SDLTexture.h"
#include "../../../common/debug/CDebug.h"

using namespace SGZ;

bool SDLTexture::createTexture ( void )
{
/** This creates and sets up a blank texture, which we sometimes need, and gets it ready to load one in if we want. */
	mTexture = NULL;
	return true;
}

bool SDLTexture::loadTexture ( const std::string &Filename )
{
/** This loads in a texture */
	SDL_Surface *temp;
	Logger.log( SGZLOG::Debug, "SGZTexture: Attempting to load: " + Filename);
	temp = IMG_Load(Filename.c_str());

	if (!temp) {
		/** YOU FAIL! */
		Logger.log( SGZLOG::Error, "SGZTexture: FAILED to load: " + Filename);
		Logger.log( SGZLOG::Error, "SGZTexture: " + std::string(IMG_GetError()) );
		/** Clean up the temp surface */
		temp = NULL;
		/** Return false though we should throw an exception*/
		return false;
	}

	/** Convert it to the current display format if different */
	mTexture = SDL_DisplayFormat( temp );

	/** Clean up the temp surface */
	SDL_FreeSurface( temp );

	return true;
}

bool SDLTexture::setColourKey( const SGZ::RGBCOLOUR &colkey)
{
	mColKey = colkey;
	return true;
}

void* SDLTexture::getTexture( void )
{
/** This returns the texture, which since it could be anything, is a void pointer */
	return mTexture;
}

bool SDLTexture::deleteTexture( void )
{
/** Deletes the memory used by this texture */
	if (mTexture)
	{
		SDL_FreeSurface(mTexture);
		return true;
	}
	else return false;
}

bool SDLTexture::blitTexture( const SGZ::VECTOR3 &vector, const SGZ::SCALER u, const SGZ::SCALER v, const SGZ::SCALER w, const SGZ::SCALER h )
{
	/// Now our Texture Rectangle
	SDL_Rect Rect;
	Rect.x=(Uint16)u;
	Rect.y=(Uint16)v;
	Rect.w=(Uint16)w;
	Rect.h=(Uint16)h;


	/// Make sure we know where we're going
	mOffset.x = (Sint16)(vector.x);
	mOffset.y = (Sint16)(vector.y);

	/// Set Colour Key
	SDL_SetColorKey(mTexture, SDL_SRCCOLORKEY, SDL_MapRGB(mTexture->format, (Uint32)mColKey.r, (Uint32)mColKey.g, (Uint32)mColKey.b));

	/// Blit from our Texture, to our Screen
	SDL_BlitSurface(mTexture, &Rect, SDL_GetVideoSurface(), &mOffset);


	//SDL_BlitSurface(Texture, NULL, SDL_GetVideoSurface(), &offset );
	return true;
}

bool SDLTexture::setColour( const SGZ::RGBCOLOUR &colour )
{
	mTexCol = colour;
	return true;
}
