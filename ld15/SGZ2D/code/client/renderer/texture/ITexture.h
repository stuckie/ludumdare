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
	\file ITexture.h
	\brief The Texture Interface

*/

#ifndef _ITEXTURE_H_
#define _ITEXTURE_H_

#include "../../../typedefs.h"
#include <string>

namespace SGZ {
	class ITexture
	{
		public:
			virtual ~ITexture() {}

			virtual bool createTexture ( void ) = 0;
			/** This creates and sets up a blank texture, which we sometimes need, and gets it ready to load one in if we want. */

			virtual bool loadTexture ( const std::string &pFilename ) = 0;
			/** This loads in a texture */

			virtual bool loadTextureMask ( const std::string &pFilename ) = 0;
			/** This loads in a texture */

			virtual void* getTexture( void ) = 0;
			/** This returns the texture, which since it could be anything, is a void pointer */

			virtual void* getTextureMask( void ) = 0;
			/** This returns the texture mask, which since it could be anything, is a void pointer */

			virtual bool deleteTexture( void ) = 0;
			/** Deletes the memory used by this texture */

			virtual bool setColourKey( const SGZ::RGBCOLOUR &pColkey ) = 0;
			/** Sets Colour Key */

			virtual bool setColour( const SGZ::RGBCOLOUR &pColour ) = 0;
			/** Sets Colour */

			virtual bool blitTexture( 	const SGZ::VECTOR3 &pVector,  const SGZ::SCALER pU, const SGZ::SCALER pV,
							const SGZ::SCALER pW, const SGZ::SCALER pH ) = 0;
			/** Blits a texture STRAIGHT to the screen */

	}; // End of ITexture

}	// End of Namespace
#endif
