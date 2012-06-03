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
	\file MEntity.h
	\brief The Enttiy Manager

*/

#ifndef _MENTITY_H_
#define _MENTITY_H_

#include "../../../typedefs.h"
#include "../../../common/data/CSLinkedlist.h"
#include <string>

namespace SGZ {
	class IEntity;
}

class MEntity
{
	public:
	MEntity();
	~MEntity();

	bool updateEntities ( float deltaTime );
	bool addEntity( SGZ::IEntity *Entity );
	bool delEntity( const std::string &pName );

	bool moveTo ( const std::string &pName, const SGZ::VECTOR3 &pMoveto );
	/** Move to direct co-ordinates */

	bool lookTo ( const std::string &pName, const SGZ::VECTOR3 &pLookto );
	/** Direction to look at ( move towards ) */

	bool moveDelta  ( const std::string &pName, const SGZ::VECTOR3 &pDelta );
	/** Move a certain amount in a certain axis */

	SGZ::VECTOR3 getPosition( const std::string &pName );
	/** Return position data */

	SGZ::VECTOR3 getDimensions( const std::string &pName );

	SGZ::VECTOR3 getLooking( const std::string &pName );

	bool scale	  ( const std::string &pName, const SGZ::SCALER value );
	bool scaleXYZ   ( const std::string &pName, const SGZ::VECTOR3 &pValue );
	/** Scale overall or in a specified axis */

	bool rotate  ( const std::string &pName, const SGZ::VECTOR3 &pValue );
	/** Rotate on a specific axis */

	bool setMaxAccel ( const std::string &pName, const SGZ::SCALER pValue );
	bool setMaxSpeed ( const std::string &pName, const SGZ::SCALER pValue );
	bool setSpeed ( const std::string &pName, const SGZ::SCALER pValue );
	SGZ::SCALER getSpeed ( const std::string &pName );
	SGZ::SCALER getAccel ( const std::string &pName );
	bool setAccel ( const std::string &pName, const SGZ::SCALER pValue );
	/** Accelerate a certain value "forward" */

	bool stop ( const std::string &pName );
	/** Stop moving/rotating/scaling immediately */

	bool setCollisionGeom ( const std::string &pName, const int pType );
	/** Set the collision type */

	std::string getAnimation( const std::string &pName );
	bool setAnimation( const std::string &pName, const std::string &pAnimName );
	bool createAnimation( const std::string &pName, const std::string &pAnimName );
	bool deleteAnimation( const std::string &pName, const std::string &pAnimName );
	bool loadFrame ( const std::string &pName, const std::string &pAnimName, const std::string &pTexName,
					 const std::string &pMaskName, const int pFrameDelay, const int pU, const int pV, const SGZ::RGBCOLOUR &pColourKey );
	/** Load up a Texture into an Animation*/

	std::string checkVar ( const std::string &pName, const std::string &pVarName );
	bool newVar( const std::string &pName, const std::string &pVarName );
	bool deleteVar( const std::string &pName, const std::string &pVarName );
	bool changeVar( const std::string &pName, const std::string &pVarName, const std::string &pValue );
	bool checkExist( const std::string &pName );

	bool setColour ( const std::string &pName, const SGZ::RGBCOLOUR &pColour );
	bool changeColour ( const std::string &pName, const SGZ::RGBCOLOUR &pOldColour, const SGZ::RGBCOLOUR &pNewColour);

	int getEntityCount(void);
	void setMaxEntities(const int pValue);
	int getCurrentMaxEntities(void);

	bool setDimensions( const std::string &pName, const SGZ::VECTOR3 &pVector );

	private:
	int mMaxEntities;
	SLinkedList<SGZ::IEntity*> mEntityList;

	SGZ::IEntity* getEntity(const std::string &pName );

};

#endif
