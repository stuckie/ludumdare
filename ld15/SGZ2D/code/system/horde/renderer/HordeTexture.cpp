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

#include "HordeTexture.h"
#if defined(REND_HORDE) || defined(REND_SDLHORDE)

HordeTexture::HordeTexture()
{

}

HordeTexture::~HordeTexture()
{

}

bool HordeTexture::createTexture ( void )
{
	/** This creates and sets up a blank texture, which we sometimes need, and gets it ready to load one in if we want. */

	return true;
}

bool HordeTexture::loadTexture ( const std::string &Filename )
{
	/** This loads in a texture */
	Texture = Horde3D::addResource( ResourceTypes::Material, Filename.c_str(), 0 );
	Horde3DUtils::loadResourcesFromDisk( "data" );

	return true;
}

bool HordeTexture::loadTextureMask ( const std::string &Filename )
{
	/** This loads in a texture */
	Texture = Horde3D::addResource( ResourceTypes::Material, Filename.c_str(), 0 );
	Horde3DUtils::loadResourcesFromDisk( "data" );

	return true;
}

void* HordeTexture::getTexture( void )
{
	/** This returns the texture, which since it could be anything, is a void pointer */

	return &Texture;
}

void* HordeTexture::getTextureMask( void )
{
	/** This returns the texture mask, which since it could be anything, is a void pointer */

	return &TextureMask;
}

bool HordeTexture::deleteTexture( void )
{
	/** Deletes the memory used by this texture */
	Horde3D::unloadResource(Texture);
	Horde3D::removeResource(Texture);

	Horde3D::releaseUnusedResources();

	return true;
}

bool HordeTexture::setColourKey( const SGZ::RGBCOLOUR &colkey )
{
	/** Sets Colour Key */
	ColourKey = colkey;

	return true;
}

bool HordeTexture::setColour( const SGZ::RGBCOLOUR &colour )
{
	/** Sets Colour */
	Colour = colour;

	return true;
}

bool HordeTexture::blitTexture( const SGZ::VECTOR3 &vector, const SGZ::SCALER u, const SGZ::SCALER v, const SGZ::SCALER w, const SGZ::SCALER h )
{
	/** Blits a texture STRAIGHT to the screen .. in a somewhat botched way! */
	Horde3D::showOverlay(	(float)vector.x,			(float)vector.y,			(float)u,		   (float)v,
							(float)vector.x +(float)w,  (float)vector.y,			(float)u+(float)w,  (float)v,
							(float)vector.x +(float)w,  (float)vector.y+(float)h,   (float)u+(float)w,  (float)v+(float)h,
							(float)vector.x,			(float)vector.y+(float)h,   (float)u,		   (float)v+(float)h,
							(int) vector.z, Texture);

	return true;
}

bool HordeTexture::blitTexture( float x1, float y1, float u1, float v1,
								float x2, float y2, float u2, float v2,
								float x3, float y3, float u3, float v3,
								float x4, float y4, float u4, float v4,
								int layer )
{
	/** Blits a texture STRAIGHT to the screen  The HORDE way! */
	Horde3D::showOverlay(	x1, y1, u1, v1,
							x2, y2, u2, v2,
							x3, y3, u3, v3,
							x4, y4, u4, v4,
							layer, Texture);

	/*  (x,y) 1 = bottom left quad   | (u,v) 1 = bottom left tex co-ords
		(x,y) 2 = bottom right quad  | (u,v) 2 = bottom right tex co-ords
		(x,y) 3 = upper right quad   | (u,v) 3 = upper right tex co-ords
		(x,y) 4 = upper left quad	| (u,v) 4 = upper left tex co-ords */

	return true;
}

#endif
