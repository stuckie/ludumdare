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
	\file main.h
	\brief Contains Prototypes for the main.cpp file

*/

#include "arch.h"	/* Seeing as sometimes we need a different entry point, we need to know which
			architecture we're currently using... damn you WinAPI!!!		*/

// PROTOTYPE FUNCTIONS
#ifndef REND_WINAPI
	int main ( void );				// Common Main Entry
#else
#include <windows.h>
	HWND ghwnd;
	void RegisterMyWindow(HINSTANCE hInstance); 	// For registering windows with Windows
	bool InitialiseMyWindow(HINSTANCE hInstance,	// For Initialising the window
				int nCmdShow);
	LRESULT CALLBACK WndProc (	HWND hWnd,	// Our Windows Message Processor
					UINT message,
					WPARAM wParam,
					LPARAM lParam);
	int WINAPI WinMain (	HINSTANCE hInstance,	// Not-so-common Main Entry ;)
				HINSTANCE hPrevInstance,
				LPSTR szCmdLine,
				int nCmdShow);
#endif
