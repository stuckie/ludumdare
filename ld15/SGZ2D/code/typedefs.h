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
	\file typedef.h
	\brief Controls some pre-defined variables and their inner values

*/

#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_
#ifdef REND_SDL
	#include "SDL/SDL.h"
#endif

namespace SGZ
{
	struct RGBCOLOUR
	{
		#if defined(PLAT_DS) || defined(PLAT_GBA) || defined(PLAT_GP32) || defined(PLAT_GP2X)
			int r, g, b;
		#elif defined (REND_SDL)
			Uint32 r, g, b;
		#else
			float r, g, b;
		#endif
	};

	struct VECTOR3
	{
		VECTOR3(void)
		:	x(0),
			y(0),
			z(0)
		{
			/* nope */
		};

		#if defined(PLAT_DS) || defined(PLAT_GBA) || defined(PLAT_GP32) || defined(PLAT_GP2X)
			VECTOR3( const int pX, const int pY, const int pZ )
			:	x(0),
				y(0),
				z(0)
			{
				x = pX;
				y = pY;
				z = pZ;
			};

			int x, y, z;
		#else
			VECTOR3( const float pX, const float pY, const float pZ )
			:	x(0),
				y(0),
				z(0)
			{
				x = pX;
				y = pY;
				z = pZ;
			};

			float x, y, z;
		#endif
	};

	#if defined(PLAT_DS) || defined(PLAT_GBA) || defined(PLAT_GP32) || defined(PLAT_GP2X)
		typedef int SCALER;
	#else
		typedef float SCALER;
	#endif

	#if defined(PLAT_DS) || defined(PLAT_GBA) || defined(PLAT_GP32) || defined(PLAT_GP2X)
		typedef int COLOURVAL;
	#elif defined(REND_SDL)
		typedef Uint32 COLOURVAL;
	#else
		typedef float COLOURVAL;
	#endif

	#define SDL_AXIS_MAX (32768);

	/* Client Defines */
	#ifndef clientRender
		#define clientRenderer (SGZ::Interpret.accessClient()->accessRenderer())
	#endif

	#ifndef clientAudio
		#define clientAudio (SGZ::Interpret.accessClient()->accessAudio())
	#endif

	#ifndef clientInput
		#define clientInput (SGZ::Interpret.accessClient()->accessController())
	#endif

	#ifndef clientGUI
		#define clientGUI (SGZ::Interpret.accessClient()->accessGUI())
	#endif

	/* Network Defines */
	#ifndef networkHost
		#define networkHost (SGZ::Interpret.accessServer()->Host())
	#endif

	/* Server Defines */
	#ifndef serverPhysics
		#define serverPhysics (SGZ::Interpret.accessServer()->World()->accessPhysics())
	#endif

	#ifndef serverAI
		#define serverAI (SGZ::Interpret.accessServer()->World()->accessAI())
	#endif

	/* Manager Defines */
	#ifndef manEntities
		#define manEntities (SGZ::Interpret.accessServer()->World()->accessEntityManager())
	#endif

	#ifndef manLevel
		#define manLevel (SGZ::Interpret.accessServer()->World()->accessLevelManager())
	#endif

	#ifndef manTextures
		#define manTextures (SGZ::Interpret.accessServer()->World()->accessTextureManager())
	#endif

} // End of Namespace

#endif // End of _TYPEDEF_H_
