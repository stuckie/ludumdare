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

#include "OFrame.h"

#include "../button/OButton.h"
#include "../../renderer/texture/OTexture.h"
#include "../../../common/debug/CDebug.h"

using namespace SGZ;

bool OFrame::updateFrame ( void )
{
	return true;
}

bool OFrame::destroyFrame ( void )
{
	return true;
}

bool OFrame::setName ( const std::string &pFrameName )
{
	mName = pFrameName;
	return true;
}

std::string OFrame::getName ( void )
{
	return mName;
}

bool OFrame::addButton(OButton *pButton)
{
	mButtonList.append(pButton);
	return true;
}

OButton* OFrame::getButton ( const std::string &pButtonName )
{
	SListIterator<OButton*> ButtonITR = mButtonList.getIterator();

	for( ButtonITR.start(); ButtonITR.valid(); ButtonITR.forth() )
		if((ButtonITR.item()->getName().compare(pButtonName))==0)
			return ButtonITR.item();

	Logger.log( SGZLOG::Warning , "Button " + pButtonName + " does not exist!\n" );
	return NULL;
}

bool OFrame::isSelected ( void )
{
	return mSelected;
}

bool OFrame::select ( const bool pValue )
{
	mSelected = pValue;
	return true;
}
