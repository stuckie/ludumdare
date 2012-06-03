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
	\file CTimer.h
	\brief The Timer Class


	Not too sure who originally wrote this actually, hehe

	It's a collaberation between Steven Campbell and Bryan Morgan.

*/

#ifndef _CTIMER_H_
#define _CTIMER_H_

#ifdef IN_SDL
#include "SDL/SDL.h"	//!< SDL has better time keeping stuff
#else
#include <ctime>	   //!< We're going to be hacky with things otherwise
#endif

namespace SGZ
{
	class Timer
	{
		private:
			int mStartTime;		//!< starting time of the timer
			int mBaseTime;		 //!< base time of the timer (current time)
			bool mRunning;		 //!< if the timer is running or not.

		public:

		/** CTimer Constructor
		// resets all variables to 0 or false
		*/
		Timer()
		:   mStartTime(0),
			mBaseTime(0),
			mRunning( false )
		{
			/* nope */
		}

		/** start function
		// starts the timer
		*/
		void start()
		{
			if (!mRunning)
			{
				#ifdef IN_SDL
					mStartTime = SDL_GetTicks();
				#else
					mStartTime = clock();
				#endif

				mRunning = true;
			}
		}

		/** stop function
		// stops the timer
		*/
		void stop()
		{
			if (mRunning)
			{
				#ifdef IN_SDL
				mBaseTime = mBaseTime + (SDL_GetTicks() - mStartTime);
				#else
				mBaseTime = mBaseTime + (clock() - mStartTime);
				#endif

				mRunning = false;
			}
		}

		/** reset function
		// resets the timer
		*/
		void reset()
		{
			#ifdef IN_SDL
				mStartTime = SDL_GetTicks();
			#else
				mStartTime = clock();
			#endif

			mBaseTime = 0;
		}

		/** stopped function
		// returns whether the timer is running or not
		*/
		bool stopped()
		{
			return !mRunning;
		}

		/** currenttime function
		// returns the current time of this timer
		*/
		int currenttime()
		{
			if (mRunning)
			{
				#ifdef IN_SDL
				return mBaseTime + (SDL_GetTicks() - mStartTime);
				#else
				return mBaseTime + (clock() - mStartTime);
				#endif
			}
			else
			{
				return mBaseTime;
			}
		}
	}; // End of CTimer

} // End of Namespace
#endif
