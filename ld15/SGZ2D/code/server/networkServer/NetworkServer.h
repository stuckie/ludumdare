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
	\file NetworkServer.h
	\brief The NetworkServer Object

*/

#ifndef __NETWORKSERVER_H_
#define __NETWORKSERVER_H_

#include "../IServer.h"

class NetworkServer : public SGZ::IServer
{
	public:
	NetworkServer() {};
	~NetworkServer() {};

	bool createInterface(void);
	bool updateServer(void);
	bool destroyInterface(void);
	bool activate(void);

	private:
};

#endif
