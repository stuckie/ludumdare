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
	\file CDebug.h
	\brief SGEngine Debug Logging Facilities

	For when things go wrong, we need to be able to log whatever we get.
	Be them errors, warnings or debug messages!

	This was taken from the SGEngine project and back ported to SGZEngine
*/

#ifndef _CDEBUG_H_
#define _CDEBUG_H_

#include "../data/CSingleton.h"
#include <string>

class string;

struct SGZLOG
{
	enum Type
	{
		Debug = 100,
		Warning,
		Error,
		Message
	};
};

namespace SGZ
{
	class CLogger : public CSingleton<CLogger>
	{
		bool mVerbose;

		public:
			CLogger();
			~CLogger();

			void log( const SGZLOG::Type pType, const std::string &pErrorString ) const;
			void setVerbosity( const bool pSet );

	}; // end of CLogger

	#define Logger CLogger::getSingleton()

} // End of Namespace

#endif
