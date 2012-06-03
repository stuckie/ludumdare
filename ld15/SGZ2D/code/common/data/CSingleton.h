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

/** -------------------------------------------------------------------------------
	\file CSingleton.h
	\brief Singleton Class

	This Singleton Class was pinched from Dr Henry Fortuna's PS2 tutorials.

	It has been modified slightly to work with newer versions of GCC by Stuckie.

	------------------------------------------------------------------------------- */

#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <assert.h>

// This class may seem a little strange if you have never seen a
// singleton before. But it is a very useful, and increasingly
// common data structure, particularly in games.

// You can think of a singleton as a nice way to have a "global"
// object, without the hassle of actually making the variable global
// and then externing it all over the place.

// If you derive your class from CSingleton, and then create a single
// instance of the object in the source file, you can then access that
// object from anywhere by calling the GetSingleton method of your class

template <typename T> class CSingleton
{
	// The one and only instance of this class
	static T * ms_Singleton;

public:
	// Sets up the one and only instance
	CSingleton()
	{
		assert(!ms_Singleton);
		//int offset = (T*)1 - (CSingleton<T>*)(T*)1;
		ms_Singleton = (T*)(this);// + offset);
	}

	// Destroys the one and only instance
	virtual ~CSingleton()
	{
		assert(ms_Singleton);
		ms_Singleton = 0;
	}

	// Returns the singleton
	static T& getSingleton()
	{
		assert(ms_Singleton);
		return (*ms_Singleton);
	}

	// Returns a pointer to the singleton
	static T* getSingletonPtr()
	{
		return ms_Singleton;
	}
};

// This might look a bit confusing, but all it does is for each new singleton type that is created
// it initialises it's static T * ms_Singleton member.
template <typename T> T * CSingleton <T>::ms_Singleton = 0;

#endif
