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
	\file main.cpp
	\brief Contains the basic start-up code and "glue" for the engine

*/

// HEADER INCLUDES
#include "main.h"
#include "arch.h"
#include "common/engine/CInterpret.h"
#include "common/debug/CDebug.h"
#include <stdlib.h>

#ifdef PLAT_GP2X
	#include "unistd.h"
#endif

#ifdef PLAT_WII
	#include <fat.h>
#endif

#ifdef PLAT_PSPDEV
	#ifndef NDEBUG
		#include <pspdebug.h>
	#endif
	#include <pspkernel.h>

	//Cause 640k ought to be enough for everybody?
	PSP_HEAP_SIZE_KB(-640);
	//Set thread attribute to user-land and enable VFPU
	PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER|PSP_THREAD_ATTR_VFPU);
#endif

#if defined(OS_WIN32)
	#define WIN32_LEAN_AND_MEAN
	#include "windows.h"
	INT WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int ) // just ignore the wincrap for now ;)
#endif

#if defined(SDL_Main)
	extern "C" int SDL_main(int nNumArgs,char **ppcArgs)
#endif

#if !defined(OS_WIN32) && !defined(SDL_Main)
	int main( void )
#endif
{
	bool error(false);
	#ifdef PLAT_WII
		if (false == fatInitDefault()) {
			SGZ::Logger.log(SGZLOG::Error, "[MAIN.CPP] SERIOUS: fatInitDefault failed.. might as well bail since we can't read anything...");
			error = true;
		}
	#endif
	if (false == error) {
		if (false == SGZ::Interpret.setup()) {
			SGZ::Logger.log(SGZLOG::Error, "[MAIN.CPP] SERIOUS: Something went REALLY wrong on INIT!");
			error = true;
		}
	}

	if (false == error) {
		while(true == SGZ::Interpret.isRunning())
			if (false == SGZ::Interpret.run()) {
				SGZ::Logger.log(SGZLOG::Error, "[MAIN.CPP] SERIOUS: Something went REALLY wrong on RUN!");
				error = true;
			}
	}

	if (false == SGZ::Interpret.shutdown()) {
		SGZ::Logger.log(SGZLOG::Error, "[MAIN.CPP] SERIOUS: Something went REALLY wrong on EXIT! but we're closing down so there's not a whole heap we can do about it...");
		error = true;
	}

	#ifdef PLAT_GP2X
		chdir("/usr/gp2x");
		execl(  "/usr/gp2x/gp2xmenu",
			"/usr/gp2x/gp2xmenu", NULL);
	#endif

	return error;
}
