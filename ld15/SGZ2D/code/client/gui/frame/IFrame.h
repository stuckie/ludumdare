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
	\file IFrame.h
	\brief The Frame Interface

*/

#ifndef _IFRAME_H_
#define _IFRAME_H_

#include <string>

class OButton;

namespace SGZ
{

	class IFrame
	{
		public:
		virtual ~IFrame() {}

		virtual bool updateFrame ( void ) = 0;
		virtual bool destroyFrame ( void ) = 0;

		virtual bool setName ( const std::string &pFrameName ) = 0;
		virtual std::string getName ( void ) = 0;

		virtual bool addButton ( OButton *pButton ) = 0;
		virtual OButton* getButton ( const std::string &pButtonName ) = 0;

		virtual bool isSelected ( void ) = 0;
		virtual bool select ( const bool pValue ) = 0;

	};
}

#endif
