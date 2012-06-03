/*
	SGZEngine
	Copyright (C) 2008 Steven Campbell

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
	\file MGui.h
	\brief The GUI Manager

*/

#ifndef _MGUI_H_
#define _MGUI_H_

#include "../../common/data/CSLinkedlist.h"
#include <string>

class OFrame;
class OButton;

class MGui
{
	public:
		MGui();
		~MGui();

		void createGui ();
		void destroyGui ();

		void createFrame ( const std::string &pFrameName );
		void destroyFrame ( const std::string &pFrameName );
		OFrame* getFrame ( const std::string &pFrameName );


		void createButton ( const std::string &pFrameName, const std::string &pButtonName );
		void destroyButton ( const std::string &pFrameName, const std::string &pButtonName );
		void setButtonTexture ( const std::string &pFrameName, const std::string &pButtonName, const std::string &pFileName, const std::string &pMaskName );
		OButton* getButton ( const std::string &pFrameName, const std::string &pButtonName );


	private:
		SLinkedList<OFrame*> mFrameList;

};

#endif
