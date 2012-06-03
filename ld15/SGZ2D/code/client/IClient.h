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
	\file IClient.h
	\brief The Client Interface

	We use a Client interface as there's several types of Clients we can create.
	For example, we can use a client for "demo record/playback", AI, or whatever else.
*/

#ifndef _ICLIENT_H_
#define _ICLIENT_H_

namespace SGZ
{
	class IClient
	{
		public:
			virtual ~IClient()
			{
				/* nope */
			}

			virtual void createInterface() = 0;
			/** Create a client interface to talk on */

			virtual void destroyInterface() = 0;
			/** Destroy a client interface */

			virtual void updateClient() = 0;
			/** Update This Client */

	}; // End of IClient

} // End of Namespace
#endif
