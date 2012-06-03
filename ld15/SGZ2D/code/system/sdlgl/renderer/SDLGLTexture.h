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

#ifndef _SDLGLTEXTURE_H_
#define _SDLGLTEXTURE_H_

#include "../../../arch.h"

#if defined(REND_OPENGL) || defined(REND_SDLGL)

#include "../../../client/renderer/texture/ITexture.h"
#include "../../../common/debug/CDebug.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class SDLGLTexture : public ITexture
{
	public:
	SDLGLTexture() {};
	~SDLGLTexture() {};

	bool CreateTexture ( void );
	/** This creates and sets up a blank texture, which we sometimes need, and gets it ready to load one in if we want. */

	bool LoadTexture ( std::string Filename );
	/** This loads in a texture */

	bool LoadTextureMask ( std::string Filename );
	/** This loads in a texture mask */

	void* GetTexture( void );
	/** This returns the texture, which since it could be anything, is a void pointer */

	void* GetTextureMask( void );
	/** This returns the texture, which since it could be anything, is a void pointer */

	bool DeleteTexture( void );
	/** Deletes the memory used by this texture */

	bool SetColourKey( SGZ::RGBCOLOUR colkey );
	/** Sets transparency */

	bool SetColour( SGZ::RGBCOLOUR colour );

	bool BlitTexture(SGZ::VECTOR3 vector, SGZ::SCALER u, SGZ::SCALER v, SGZ::SCALER w, SGZ::SCALER h);
	/** Blit Texture straight to Screen */

	private:

	SDL_Surface *SDLTexture;
	GLuint GLTexture, GLTextureMask;

	int width, height;

	SGZ::RGBCOLOUR colour;
};

#endif
#endif
