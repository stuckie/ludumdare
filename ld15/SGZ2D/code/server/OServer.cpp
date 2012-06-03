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
	\file OServer.cpp
	\brief The Server Object

*/

#include "OServer.h"
#include "gameServer/GameServer.h"
#include "networkServer/NetworkServer.h"

using namespace SGZ;

bool OServer::createInterface(void)
{
	/** Create a script interface */
	mGameWorld = new GameServer;
	mGameWorld->createInterface();
	Logger.log( SGZLOG::Debug, "Server Interface Created.\n");

	/**Create a Host Server */
	mHostServer = new NetworkServer;
	mHostServer->createInterface();
	Logger.log( SGZLOG::Debug, "Host Server Created.\n");
	return true;
}

bool OServer::createHostServer(void)
{
	/**Create a Host Server */
	mHostServer->activate();
	return true;
}

bool OServer::destroyInterface(void)
{
	/** Destroy a script interface */
	Logger.log( SGZLOG::Debug, "Server Interface Destroyed.\n");
	return true;
}

bool OServer::updateServer(void)
{
	/** Update the server interface */
	if(mGameWorld)
		mGameWorld->updateServer();
	if(mHostServer)
		mHostServer->updateServer();

	return true;
}
