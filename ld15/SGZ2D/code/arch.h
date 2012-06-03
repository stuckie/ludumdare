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
 \file arch.h
 \brief Just sets the defines as to what we're building for

 As of 25th April 2009, this isn't exactly used anymore... add defines to your Makefile for what you're compiling in!
 This just lists the support which should be in the engine somewhere ;)

 Surprisingly, this file HAS been cleaned up a whole bunch as of 8th December 2008
 It used to have links to pretty much every major system from Dreamcast to NDS, Mac OS to PS3Linux
 Though a lot of them do have bits of code to make them work and do _something_ ... they're hugely incomplete.
 They're marked as TODO: however.. as they may get proper support later
 -- Stuckie
*/

#ifndef ARCH_H
	#define ARCH_H			// Make sure we do NOT include this multiple times

	// PLATFORM DEFINES		// What platform we're going for..
	//#define PLAT_A320		// Support for the Dingoo A320
	//#define PLAT_GP32		// TODO: PLAT_GP32 Handheld -- http://en.wikipedia.org/wiki/GP32 -- Uses devkitARM kit
	//#define PLAT_GP2X		// GP2X Handheld -- http://www.gp2x.co.uk -- Uses Open2X kit
	//#define PLAT_GP2XWIZ		// TODO: PLAT_GP2X Wiz Handheld -- I think it uses Open2X..
	//#define PLAT_PANDORA		// TODO: PLAT_Pandora Handheld -- http://www.openpandora.org -- Open2X again?
	//#define PLAT_FREERUNNER	// TODO: PLAT_Freerunner OpenMoko phone -- base support added by Zear
	//#define PLAT_GBA		// TODO: PLAT_Gameboy Advance -- Using the devkitARM kit
	//#define PLAT_DS		// TODO: PLAT_Nintendo DS -- Using the devkitARM kit
	//#define PLAT_GC		// TODO: PLAT_Nintendo Gamecube -- Uses the devkitPPC kit
	//#define PLAT_WII		// TODO: PLAT_Nintendo Wii -- Uses the devkitPPC kit
	//#define PLAT_DC		// TODO: PLAT_SEGA Dreamcast -- Uses the KallistiOS setup
	//#define PLAT_PSX		// TODO: PLAT_PSX Console -- It's a GCC compiler setup again, it's here for fun :)
	//#define PLAT_PS2LINUX		// TODO: PLAT_PS2 Console -- Using PS2Linux kit - I have code for it, just needs reimplemented
	//#define PLAT_PS3LINUX		// TODO: PLAT_PS3 Console -- Using Linux (YellowDog)
	//#define PLAT_PS2DEV		// TODO: PLAT_PS2 Console -- Using PS2DEV Homebrew kit -- http://www.ps2dev.org
	//#define PLAT_PSPDEV		// TODO: PLAT_PSP Handheld -- Using PSPDEV Homebrew kit -- http://www.ps2dev.org -- currently using SDL..
	//#define PLAT_PS3DEV		// TODO: PLAT_PS3 Console -- Using PS3DEV Homebrew kit -- http://www.ps2dev.org
	//#define PLAT_MACOSX		// TODO: PLAT_Mac OS X -- It's BSD based so should get away with Linux code, use XCode and stick to SDL
	//#define PLAT_MACCLASSIC	// TODO: PLAT_Mac OS 9< -- Stick to SDL and should be ok.. MPW seems to work with SDL quite happily too
	//#define PLAT_PC		// PC -- Remember to pick the OS below!

	/* DEVKIT AVAILABILITY -- Remember, these are homebrew, so some form of using homebrew may be required - flashcart/modchip/etc
	PS2/PSP/PS3 - www.ps2dev.org
	GP2X - http://wiki.open2x.org
	GP32/GBA/DS/Gamecube/PSP - http://www.devkitpro.org
	Dreamcast - http://gamedev.allusion.net/softprj/kos
	PSX - http://www.hitmen-console.org for compiler/assemblers and http://jum.pdroms.de has some info on stuff
	*/

	/* API COMPATIBILITY -- To aid your madness of figuring out what works on what
	SDL - GP32, GP2X, Dreamcast, PS2Linux( VERY POORLY ), Windows, Mac OS / X, PSPDEV, DS, Linux
	OpenGL - Windows, Linux, Mac OS / X, PSPDEV ( of sorts ), DS ( of sorts ) and Wii ( of sorts ), probably PS3 too but not looked (think its GL ES)
	OpenGL ES 1 - Wiz, Pandora, PSPDEV ( of sorts )
	OpenGL ES 2 - Pandora
	OIS - Windows, Linux, Mac OS X
	MikMod - GP2X, Linux, PS2Linux( VERY POORLY )
	OpenAL - Linux, Windows, Mac OS X
	OGRE - Linux, Windows, Mac OS X
	Direct X and WinAPI - Windows
	SPS2 - PS2Linux
	GP32, GP2X, DS, GBA, GC, PSX, PS2DEV, PSPDEV and DC all have their own little APIs too.. which may have flags at a later date

	Shader Support > CG - Windows, Linux, Mac OS X | HLSL - Windows | GLSL - Windows, Linux, Mac OS X, Pandora (ES), Wiz (ES)
	*/

	// ENGINE DEFINE		// These should be taken care of by build targets - these are for make file targets
	//#define SGZ_2D		// Specifically define 2D Support
	//#define SGZ_3D		// Specifically define 3D Support

	// 2D RENDERER DEFINES
	#ifdef SGZ2D
		//#define REND_SDL	// Render just through SDL -- http://www.libsdl.org -- SGZ2D Default for Desktop Systems
		//#define REND_OPENGL	// TODO: Render just through OpenGL -- http://www.opengl.org -- watch the window handling!
		//#define REND_GLES1	// TODO: Render through GL ES 1
		//#define REND_GLES2	// TODO: Render through GL ES 2
		//#define REND_SDLGL	// TODO: Render OpenGL through an SDL window -- I have code, just needs redone
		//#define REND_DIRECTX	// TODO: Render just through DirectX -- Needs the WinAPI window handling nonsense
		//#define REND_SDLDX	// TODO: Render DirectX through an SDL window ;) - I have the code ...
		//#define REND_SPS2	// TODO: Render through SPS2 (PS2 only, this is the 2D optimised version) -- I have the code
		//#define REND_WINAPI	// TODO: Render WinAPI -- I have the code from PowerOUT that should work mostly ok
	#endif

	// 3D RENDERER DEFINES
	#ifdef SGZ3D
		//#define REND_SDLGL	// TODO: Render OpenGL through an SDL window -- will be SGZ3D Default - have the code
		//#define REND_OPENGL	// TODO: Render just through OpenGL -- http://www.opengl.org
		//#define REND_GLES1	// TODO: Render through GL ES 1
		//#define REND_GLES2	// TODO: Render through GL ES 2
		//#define REND_OGRE	// TODO: Render using OGRE -- I have code, needs reworked though
		//#define REND_HORDE	// TODO: Render using HORDE -- need to set up window yourself
		//#define REND_SDLHORDE	// TODO: Render using HORDE with SDL to back things up -- I have the code
		//#define REND_DIRECTX	// TODO: Render just through DirectX
		//#define REND_SDLDX	// TODO: Render DirectX through an SDL window ;) -- have the code
		//#define REND_SPS2	// TODO: Render through SPS2 (PS2 only, 3D optimised) -- again, have the code!
	#endif

	// SOUND DEFINES		// Which sound engine to use, SDL, Mikmod, DirectX
	//#define SND_DIRECTX		// TODO: Sound and Music through DirectX - obsoleted by XACT, which I don't have code for...
	//#define SND_XACT		// TODO: Sound and Music through XACT - I have no code for this.. I do for DSound though
	//#define SND_SDL		// Sound and Music through SDL (requires SDL_mixer compiled in)
	//#define SND_OPENAL		// TODO: Sound and Music through OpenAL
	//#define SND_PS2LINUX		// "automatically" pulled in via PLAT_PS2LINUX but just for completeness

	// INPUT DEFINES		// Which Input Engine to use, SDL, OIS, DirectX
	//#define IN_SDL		// Use SDL for Input (requires an SDL-compat renderer as we need the window for events!)
	//#define IN_OIS		// TODO: Use Open Input System for Input - I have the code from Labyrinth
	//#define IN_DIRECTX		// TODO: Use DirectX for Input
	//#define IN_WINAPI		// TODO: Use WinAPI for Input - possibly useless, what with DInput..

	// OS DEFINES			// Which Operating System we're compiling on PC for Win32/64, Linux
	//#define OS_WIN32		// Yay for Windows needing some extra crap to play nice at times
	//#define OS_WIN64		// Placeholder .. may need at some point..
	//#define OS_LINUX		// Mainly for OGRE+SDL's different windowing system
	//#define GP2X_OPEN2X		// Flag for the Open2X firmware on GP2X
	//#define GP2X_GPH		// Flag for the official GPH firmware on the GP2X

	// NETWORKING DEFINES		// Which Networking Library we will use
	//#define NET_SDL		// TODO: Use SDL'S Networking library .. takes care of endian issues ;)
	//#define NET_BSD		// TODO: BSD Sockets - I have the code for a DIS, just needs cleaned
	//#define NET_WIN		// TODO: WinSock - Again, I have the code for a DIS, just needs cleaned
	//#define NET_OFF		// Turn networking OFF -- this is a "dummy" interface

	// SHADER SUPPORT		// Which define for shaders to use -- this is probably useless
	//#define SHADER_CG		// Use CG Shaders
	//#define SHADER_GLSL		// Use GLSL Shaders (GSlang)
	//#define SHADER_HLSL		// Use HLSL Shaders (FX Shaders) - Windows Only

	// GUI SUPPORT
	//#define GUI_CEGUI		// TODO: Use CEGUI - Have the code
	//#define GUI_QT		// TODO: Use QT for gui stuff
	//#define GUI_MOTIF		// TODO: Use MOTIF
	//#define GUI_GTK		// TODO: Use GTK
	//#define GUI_SGZ		// TODO: Use own gui - needs a lot of work still
	//#define GUI_WXWIDGETS		// TODO: Use WxWidgets

	// SCRIPT SUPPORT
	//#define SCRIPT_LUA		// Use Lua
	//#define SCRIPT_PYTHON		// TODO: Use Python - probably never be done
	//#define SCRIPT_RUBY		// TODO: Use Ruby - also highly unlikely

	// PHYSICS SUPPORT		// Which Physics library to use... there are a few multi platform ones
	//#define PHYSICS_ODE		// TODO: ODE - Open Dynamics Engine -- http://www.ode.org - have the code, needs cleaned though

	// EXTRAS SUPPORT		// Random things to support
	//#define amBX_ON		// TODO: Use amBX! - we had support in at one point! Can't really have it anymore though :(
	/* May add more when I have time to even attempt to support them... */


	// ARCH SPECIFIC DEFINES

#endif

#include "typedefs.h" /* To avoid a cyclic dependency, this is at the bottom out the road */
