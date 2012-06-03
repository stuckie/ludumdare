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
	\file IButton.h
	\brief The Button Interface

*/

#ifndef _IBUTTON_H_
#define _IBUTTON_H_

#include "../../../typedefs.h"
#include <string>

namespace SGZ
{
	class IButton
	{
		public:
		virtual ~IButton() {}

		virtual bool updateButton ( void ) = 0;
		virtual bool destroyButton ( void ) = 0;

		virtual bool setName ( const std::string &pButtonName ) = 0;
		virtual std::string getName ( void ) = 0;

		virtual bool isSelected ( void ) = 0;
		virtual bool select ( const bool &pValue ) = 0;

		virtual bool createState ( const std::string &pState ) = 0;
		virtual bool loadTexture ( const std::string &pState, const std::string &pFilename ) = 0;
		virtual bool deleteState ( const std::string &pState ) = 0;
		virtual bool changeState ( const std::string &pState ) = 0;
		virtual std::string getState ( void ) = 0;

		virtual bool setPosition ( const SGZ::VECTOR3 &pVector ) = 0;
		virtual bool setColour ( const SGZ::RGBCOLOUR &pColour ) = 0;
		virtual bool setSize ( const SGZ::VECTOR3 &pVector ) = 0;
	};
}

#endif

