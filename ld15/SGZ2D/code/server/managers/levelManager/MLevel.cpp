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

// TODO: Completely rewrite the LevelManager!

#include "MLevel.h"
#include "../../../common/engine/CInterpret.h"
#include "../../../common/debug/CDebug.h"
#include "../../../common/entities/IEntity.h"
#include "../../../client/renderer/texture/OTexture.h"
#include "../../OServer.h"
#include "../../gameServer/GameServer.h"
#include "../textureManager/MTexture.h"

bool MLevel::NewLevel ( int x, int y, int z )
{
	LevelMap->resize( x, y, z );
	Clear();
	return true;
}

bool MLevel::Clear( void )
{
	int tempx, tempy, tempz,x,y,z;
	tempx = LevelMap->width();
	tempy = LevelMap->height();
	tempz = LevelMap->depth();
	delete LevelMap;

	LevelMap = new Array3D<SGZTile*>(tempx, tempy, tempz);

	for( z = 0; z < tempz; z++ )
	{
		for( y = 0; y < tempy; y++ )
		{
			for( x = 0; x < tempx; x++ )
			{
				SGZTile *NewTile = new SGZTile;
				NewTile->Name = "none";
				NewTile->Type = "none";
				NewTile->VarITR = NewTile->VarList.getIterator();

				LevelMap->get(x,y,z) = NewTile;

			}
		}
	}

	return true;
}

bool MLevel::AddTile( std::string Name, std::string Type, int x, int y, int z)
{
	LevelMap->get(x,y,z)->Name = Name;
	LevelMap->get(x,y,z)->Type = Type;
	return true;
}

bool MLevel::DelTile ( std::string Name )
{
	int sizex, sizey, sizez, x,y,z;
	sizex = LevelMap->width();
	sizey = LevelMap->height();
	sizez = LevelMap->depth();
	for( z = 0; z < sizez; z++ )
	{
		for( y = 0; y < sizey; y++ )
		{
			for( x = 0; x < sizex; x++ )
			{
				if (LevelMap->get( x, y, z )->Name.compare(Name)==0)
				{
					delete LevelMap->get(x,y,z);
					return true;
				}
			}
		}
	}

	SGZ::Logger.log( SGZLOG::Warning, "Tile " + Name + " does not exist!\n");
	return false;
}

bool MLevel::SetSize ( int x, int y, int z )
{
	LevelMap->resize( x, y, z );
	Clear();
	return true;
}

bool MLevel::TexTile(std::string Name, std::string TexName, std::string MaskName, SGZ::SCALER u, SGZ::SCALER v, SGZ::SCALER w, SGZ::SCALER h, SGZ::RGBCOLOUR key)
{
	int sizex, sizey, sizez, x,y,z;
	sizex = LevelMap->width();
	sizey = LevelMap->height();
	sizez = LevelMap->depth();
	for( z = 0; z < sizez; z++ )
	{
		for( y = 0; y < sizey; y++ )
		{
			for( x = 0; x < sizex; x++ )
			{
				if (LevelMap->get( x, y, z )->Name.compare(Name)==0)
				{
					LevelMap->get(x,y,z)->TexName = TexName;
					LevelMap->get(x,y,z)->MaskName = MaskName;
					LevelMap->get(x,y,z)->u = u;
					LevelMap->get(x,y,z)->v = v;
					LevelMap->get(x,y,z)->w = w;
					LevelMap->get(x,y,z)->h = h;
					SGZ::Interpret.accessServer()->World()->accessTextureManager()->setColourKey(TexName, key);
					return true;
				}
			}
		}
	}

	SGZ::Logger.log( SGZLOG::Warning, "Tile " + Name + " does not exist!\n");
	return false;
}

bool MLevel::NewVar( std::string Name, std::string VarName )
{
	int sizex, sizey, sizez, x,y,z;
	sizex = LevelMap->width();
	sizey = LevelMap->height();
	sizez = LevelMap->depth();
	for( z = 0; z < sizez; z++ )
	{
		for( y = 0; y < sizey; y++ )
		{
			for( x = 0; x < sizex; x++ )
			{
				if (LevelMap->get( x, y, z )->Name.compare(Name)==0)
				{
					SGZVarGroup *Variable = new SGZVarGroup;
					Variable->Name = VarName;
					Variable->Variable = "none";
					LevelMap->get(x,y,z)->VarList.append(Variable);

					return true;
				}
			}
		}
	}

	SGZ::Logger.log( SGZLOG::Warning, "Tile " + Name + " does not exist!\n");
	return false;
}

bool MLevel::DeleteVar( std::string Name, std::string VarName )
{
	int sizex, sizey, sizez, x, y, z;
	sizex = LevelMap->width();
	sizey = LevelMap->height();
	sizez = LevelMap->depth();
	for( z = 0; z < sizez; z++ )
	{
		for( y = 0; y < sizey; y++ )
		{
			for( x = 0; x < sizex; x++ )
			{
				if (LevelMap->get( x, y, z )->Name.compare(Name)==0)
				{
					LevelMap->get( x, y, z )->VarITR = LevelMap->get( x, y, z )->VarList.getIterator();

					for( LevelMap->get( x, y, z )->VarITR.start(); LevelMap->get( x, y, z )->VarITR.valid(); LevelMap->get( x, y, z )->VarITR.forth() )
						if(LevelMap->get( x, y, z )->VarITR.item()->Name.compare(VarName)==0)
						{
							LevelMap->get( x, y, z )->VarList.remove(LevelMap->get( x, y, z )->VarITR);
							return true;
						}
					SGZ::Logger.log( SGZLOG::Warning, "Variable " + VarName + " does not exist!\n");
				}
			}
		}
	}

	SGZ::Logger.log( SGZLOG::Warning, "Tile " + Name + " does not exist!\n");
	return false;
}

bool MLevel::ChangeVar ( std::string Name, std::string VarName, std::string Value )
{
	int sizex, sizey, sizez, x,y,z;
	sizex = LevelMap->width();
	sizey = LevelMap->height();
	sizez = LevelMap->depth();
	for( z = 0; z < sizez; z++ )
	{
		for( y = 0; y < sizey; y++ )
		{
			for( x = 0; x < sizex; x++ )
			{
				if (LevelMap->get( x, y, z )->Name.compare(Name)==0)
				{
					LevelMap->get( x, y, z )->VarITR = LevelMap->get( x, y, z )->VarList.getIterator();

					for( LevelMap->get( x, y, z )->VarITR.start(); LevelMap->get( x, y, z )->VarITR.valid(); LevelMap->get( x, y, z )->VarITR.forth() )
						if((LevelMap->get( x, y, z )->VarITR.item()->Name.compare(VarName))==0)
						{
							LevelMap->get( x, y, z )->VarITR.item()->Variable = Value;
							return true;
						}
					SGZ::Logger.log( SGZLOG::Warning, "Variable " + VarName + " does not exist!\n");
				}
			}
		}
	}

	SGZ::Logger.log( SGZLOG::Warning, "Tile " + Name + " does not exist!\n");
	return false;
}

std::string MLevel::CheckVar( std::string Name, std::string VarName )
{
	int sizex, sizey, sizez, x,y,z;
	sizex = LevelMap->width();
	sizey = LevelMap->height();
	sizez = LevelMap->depth();
	for( z = 0; z < sizez; z++ )
	{
		for( y = 0; y < sizey; y++ )
		{
			for( x = 0; x < sizex; x++ )
			{
				if (LevelMap->get( x, y, z )->Name.compare(Name)==0)
				{
					LevelMap->get( x, y, z )->VarITR = LevelMap->get( x, y, z )->VarList.getIterator();

					for( LevelMap->get( x, y, z )->VarITR.start(); LevelMap->get( x, y, z )->VarITR.valid(); LevelMap->get( x, y, z )->VarITR.forth() )
						if((LevelMap->get( x, y, z )->VarITR.item()->Name.compare(VarName))==0)
							return LevelMap->get( x, y, z )->VarITR.item()->Variable;

					SGZ::Logger.log( SGZLOG::Warning, "Variable " + VarName + " does not exist!\n");
				}
			}
		}
	}

	SGZ::Logger.log( SGZLOG::Warning, "Tile " + Name + " does not exist!\n");

	return "none";
}

bool MLevel::CheckExist( std::string TileName )
{
	int sizex, sizey, sizez, x,y,z;
	sizex = LevelMap->width();
	sizey = LevelMap->height();
	sizez = LevelMap->depth();

	for( z = 0; z < sizez; z++ )
		for( y = 0; y < sizey; y++ )
			for( x = 0; x < sizex; x++ )
				if (LevelMap->get( x, y, z )->Name.compare(TileName)==0)
					return true;

	return false;
}

bool MLevel::RenderLevel( int layer, int startX, int startY, int endX, int endY, SGZ::SCALER cameraX, SGZ::SCALER cameraY )
{
	int z(layer);
	int tileX(0);
	int tileY(0);
	
	if (0 > startX)
		startX = 0;
	if (0 > startY)
		startY = 0;
	if (LevelMap->width() < endX)
		endX = LevelMap->width();
	if (LevelMap->height() < endY)
		endY = LevelMap->height();

	for( int y = startY; y < endY; y++ ) {
		++tileY;
		tileX = 0;
		for( int x = startX; x < endX; x++ ) {
		++tileX;
			if (!LevelMap->get( x, y, z )->Name.compare("none")==0)
			{
				SGZ::VECTOR3 position;
				position.x = (tileX * LevelMap->get(x,y,z)->w) + cameraX;
				position.y = (tileY * LevelMap->get(x,y,z)->h) + cameraY;
				position.z = z;
				SGZ::Interpret.accessServer()->World()->accessTextureManager()->blitTexture(
				LevelMap->get(x,y,z)->TexName, position, LevelMap->get(x,y,z)->u, LevelMap->get(x,y,z)->v,
				LevelMap->get(x,y,z)->w, LevelMap->get(x,y,z)->h  );
			}
		}
	
}
	return true;
}

std::string MLevel::GetType(int x, int y, int z )
{
	if (LevelMap->get(x,y,z))
		return LevelMap->get(x,y,z)->Type;
	else
		return "none";
}
