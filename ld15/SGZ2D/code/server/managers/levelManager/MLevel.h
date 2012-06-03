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
	\file MLevel.h
	\brief The Level Manager

*/

#ifndef _MLEVEL_H_
#define _MLEVEL_H_

#include "../../../typedefs.h"
#include "../../../common/data/CArray3D.h"
#include "../../../common/data/CSLinkedlist.h"
#include <string>

class SGZVarGroup;

class SGZTile
{
	public:
		SGZTile()
		:   Name(),
			TexName(),
			MaskName(),
			Type("none"),
			u(),
			v(),
			w(),
			h(),
			key(),
			VarList(),
			VarITR()
		{

		}

		~SGZTile()
		{
		}

		std::string Name;

		std::string TexName;
		std::string MaskName;
		std::string Type;
		SGZ::SCALER u,v,w,h;
		SGZ::RGBCOLOUR key;

		SLinkedList<SGZVarGroup*> VarList;
		SListIterator<SGZVarGroup*> VarITR;
};

class MLevel
{
	private:

	Array3D<SGZTile*> *LevelMap;

	public:

	MLevel()
	: LevelMap( new Array3D<SGZTile*>(0,0,0) )
	{
		/* nope */
	}

	MLevel( const MLevel&)
	: LevelMap(  )
	{
		/* nope */
	}

	MLevel operator= ( const MLevel& )
	{
		throw("");
	}

	~MLevel()
	{
	}

	bool NewLevel( int x, int y, int z);
	bool SetSize( int x, int y, int z );
	bool AddTile( std::string Name, std::string Type, int x, int y, int z );
	bool TexTile( std::string Name, std::string TexName, std::string MaskName, SGZ::SCALER u, SGZ::SCALER v, SGZ::SCALER w, SGZ::SCALER h, SGZ::RGBCOLOUR key );
	bool DelTile( std::string Name );

	bool Clear( void );
	bool RenderLevel( int layer, int startX, int startY, int endX, int endY, SGZ::SCALER cameraX, SGZ::SCALER cameraY );
	std::string GetType(int x, int y, int z);

	std::string CheckVar ( std::string Name, std::string VarName );
	bool NewVar( std::string Name, std::string VarName );
	bool DeleteVar( std::string Name, std::string VarName );
	bool ChangeVar( std::string Name, std::string VarName, std::string Value );
	bool CheckExist( std::string Name );




};

#endif

