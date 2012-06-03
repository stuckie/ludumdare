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
#if defined(REND_HORDE) || defined(REND_SDLHORDE)
#include "../../../client/renderer/texture/ITexture.h"
#include <Horde3D.h>
#include <Horde3DUtils.h>

class HordeTexture : public ITexture
{
	public:
	HordeTexture();
	~HordeTexture();

	bool createTexture ( void );
	/** This creates and sets up a blank texture, which we sometimes need, and gets it ready to load one in if we want. */

	bool loadTexture ( const std::string &Filename );
	/** This loads in a texture */

	bool loadTextureMask ( const std::string &Filename );
	/** This loads in a texture */

	void* getTexture( void );
	/** This returns the texture, which since it could be anything, is a void pointer */

	void* getTextureMask( void );
	/** This returns the texture mask, which since it could be anything, is a void pointer */

	bool deleteTexture( void );
	/** Deletes the memory used by this texture */

	bool setColourKey( const SGZ::RGBCOLOUR &colkey );
	/** Sets Colour Key */

	bool setColour( const SGZ::RGBCOLOUR &colour );
	/** Sets Colour */

	bool blitTexture( const SGZ::VECTOR3 &vector , const SGZ::SCALER u, const SGZ::SCALER v, const SGZ::SCALER w, const SGZ::SCALER h );
	/** Blits a texture STRAIGHT to the screen */

	bool blitTexture(		   float x1, float y1, float u1, float v1,
								float x2, float y2, float u2, float v2,
								float x3, float y3, float u3, float v3,
								float x4, float y4, float u4, float v4,
								int layer );
	/** Horde-specific Overlay Fun! */

	private:
	ResHandle Texture, TextureMask;

	SGZ::RGBCOLOUR ColourKey, Colour;


};

#endif
