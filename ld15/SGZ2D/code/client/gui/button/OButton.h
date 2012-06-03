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
	\file OButton.h
	\brief The Button Object

*/

#ifndef _OBUTTON_H_
#define _OBUTTON_H_

#include "IButton.h"
#include "ButtonStates.h"
#include "../../../common/data/CSLinkedlist.h"

class OButton : public SGZ::IButton
{
	public:

		OButton();
		~OButton();

		bool updateButton ( void );
		bool destroyButton ( void );

		bool setName ( const std::string &pButtonName );
		std::string getName ( void );

		bool ssSelected ( void );
		bool select ( const bool pValue );

		bool createState ( const std::string &pState );
		bool loadTexture ( const std::string &pState, const std::string &pFilename );
		bool deleteState ( const std::string &pState );
		bool changeState ( const std::string &pState );
		std::string getState ( void );

		bool setPosition ( const SGZ::VECTOR3 &pVector );
		bool setColour ( const SGZ::RGBCOLOUR &pColour );
		bool setSize ( const SGZ::VECTOR3 &pVector );

	private:

		std::string mName;

		SGZ::VECTOR3 mPosition;
		SGZ::RGBCOLOUR mColour;
		SGZ::VECTOR3 mDimensions;

		bool mSelected;

		SLinkedList<ButtonStates*> mStateList;
};

#endif
