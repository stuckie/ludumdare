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
	\file OServer.h
	\brief The Server Object

	The Server Interface is a link to the Local Game Server and Networked Server
*/

#ifndef _OSERVER_H_
#define _OSERVER_H_

#include "IServer.h"
#include "../common/debug/CDebug.h"

class GameServer;
class NetworkServer;

class OServer : public SGZ::IServer
{
	public:

		OServer()
		:   mGameWorld(NULL),
			mHostServer(NULL)
		{
			/* nope */
		}

		OServer( const OServer& )
		:   mGameWorld(NULL),
			mHostServer(NULL)
		{
			/* nope */
		}

		OServer operator=( const OServer& )
		{
			throw("nope");
		}

		~OServer()
		{
			/* nope */
		}

		bool createInterface();
		/* Create a script interface */

		bool destroyInterface();
		/* Destroy a script interface */

		bool updateServer();
		/* Update the server interface */

		bool createHostServer();
		/* Create a Host Server */

		GameServer* World() { return mGameWorld; };
		NetworkServer* Host() { return mHostServer; };

	private:
		GameServer* mGameWorld;
		NetworkServer* mHostServer;

}; // End of OServer

#endif
