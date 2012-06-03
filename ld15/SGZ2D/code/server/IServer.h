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
	\file IServer.h
	\brief The Server Interface

	We use a Server interface as there's several types of Servers we can create.
	For example, Remote/Local Server as well as Listen/Dedicated Server
*/

#ifndef _ISERVER_H_
#define _ISERVER_H_

namespace SGZ
{
	class IServer
	{
		public:
		virtual ~IServer()
		{
			/* nope */
		}

		virtual bool createInterface() = 0;
		/* Create a Server interface to talk on */

		virtual bool destroyInterface() = 0;
		/* Destroy a Server interface */

		virtual bool updateServer() = 0;
		/* Update the Server interface */

	}; // End of IServer

} // End of Namespace

#endif
