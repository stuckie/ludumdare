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
	\file OFrame.h
	\brief The Frame Object

*/

#ifndef _OFRAME_H_
#define _OFRAME_H_

#include "IFrame.h"
#include "../../../typedefs.h"
#include "../../../common/data/CSLinkedlist.h"

class OTexture;
class OButton;

class OFrame : public SGZ::IFrame
{
		public:
		OFrame()
		:   mName(),
			mPosition(),
			mDimensions(),
			mColour(),
			mSelected(false),
			mFrameSkin(),
			mButtonList()
		{
			/* nope */
		}

		OFrame(const OFrame&)
		:   mName(),
			mPosition(),
			mDimensions(),
			mColour(),
			mSelected(false),
			mFrameSkin(),
			mButtonList()
		{
			throw("TODO: OFrame");
		}

		OFrame operator=(const OFrame&)
		{
			throw("TODO: OFrame");
		}

		~OFrame()
		{
		}

		bool updateFrame ( void );
		bool destroyFrame ( void );

		bool setName ( const std::string &pFrameName );
		std::string getName ( void );

		bool addButton ( OButton *pButton );
		OButton* getButton ( const std::string &pButtonName );

		bool isSelected ( void );
		bool select ( const bool pValue );


		private:

		std::string mName;

		SGZ::VECTOR3 mPosition;
		SGZ::VECTOR3 mDimensions;
		SGZ::RGBCOLOUR mColour;

		bool mSelected;

		OTexture *mFrameSkin;

		SLinkedList<OButton*> mButtonList;
};

#endif
