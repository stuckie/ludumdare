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
	\file CInterpret.h
	\brief The Interpreter Header

*/

#ifndef _CINTERPRET_H_
#define _CINTERPRET_H_

#include "../../typedefs.h"
#include "../data/CSingleton.h"
#include "../data/CSLinkedlist.h"

class OClient;
class OServer;
class OScript;

namespace SGZ
{
	class CInterpret : public CSingleton<CInterpret>
	{

		private:
			OScript	 *mScriptObject;
			OClient	 *mClientObject;
			OServer	 *mServerObject;
			Uint32 mLastTime;

		protected:

			bool mRunStatus;

		public:

			CInterpret()
			:	mScriptObject( NULL ),
				mClientObject( NULL ),
				mServerObject( NULL ),
				mRunStatus(true)
			{
				/* nope... */
			}

			CInterpret(const CInterpret&)
			:	mScriptObject( NULL ),
				mClientObject( NULL ),
				mServerObject( NULL ),
				mRunStatus(false)
			{
				assert ("THERE CAN BE ONLY ONE INTERPRETER!");
			}

			CInterpret & operator=(const CInterpret&)
			{
				assert ("THERE CAN BE ONLY ONE INTERPRETER!");
			}

			~CInterpret()
			{
				/* nope... */
			}

			bool setup();
			bool run();
			bool shutdown();
			void firstRun() const;

			void updateInterfaces();

			OClient *accessClient() { return mClientObject; }

			OServer *accessServer() { return mServerObject; }

			OScript *accessScript() { return mScriptObject; }

			inline bool isRunning() { return mRunStatus; }

			inline void quit() { mRunStatus = false; }

	}; // End of Class

	#define Interpret CInterpret::getSingleton()

} // End of Namespace

#endif
