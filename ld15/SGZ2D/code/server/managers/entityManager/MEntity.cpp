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

#include "MEntity.h"

#include "../../../common/debug/CDebug.h"
#include "../../../common/entities/IEntity.h"

using namespace SGZ;

MEntity::MEntity()
:   mMaxEntities(0),
	mEntityList()
{
	/** Constructor */
	mMaxEntities = 0;
}

MEntity::~MEntity()
{
	/** Destructor */
	SListIterator<IEntity*> EntityListITR = mEntityList.getIterator();

	EntityListITR.start();
	while (EntityListITR.valid())
	{
		mEntityList.remove(EntityListITR);
		EntityListITR.forth();
	}
}

int MEntity::getEntityCount( void )
{
	return mEntityList.size();
}

void MEntity::setMaxEntities( const int pValue )
{
	mMaxEntities = pValue;
}

int MEntity::getCurrentMaxEntities( void )
{
	return mMaxEntities;
}

bool MEntity::addEntity(IEntity *Entity)
{
	/** Add an Entity */
	mEntityList.append(Entity);

	return true;
}

bool MEntity::updateEntities( float deltaTime )
{
	/** Update Entities */
	SListIterator<IEntity*> EntityListITR = mEntityList.getIterator();
	for( EntityListITR.start(); EntityListITR.valid(); EntityListITR.forth() )
		EntityListITR.item()->Update(deltaTime);

	return true;
}

bool MEntity::checkExist(const std::string &pName)
{
	/** Check an Entity */
	SListIterator<IEntity*> EntityListITR = mEntityList.getIterator();
	for( EntityListITR.start(); EntityListITR.valid(); EntityListITR.forth() )
		if(EntityListITR.item()->GetName().compare(pName)==0)
			return true;

	return false;
}

IEntity* MEntity::getEntity(const std::string &pName)
{
	/** Check an Entity */
	SListIterator<IEntity*> EntityListITR = mEntityList.getIterator();
	for( EntityListITR.start(); EntityListITR.valid(); EntityListITR.forth() )
		if(EntityListITR.item()->GetName().compare(pName)==0)
			return EntityListITR.item();

	return NULL;
}

bool MEntity::delEntity(const std::string &pName)
{
	/** Remove an Entity */
	SListIterator<IEntity*> EntityListITR = mEntityList.getIterator();
	for( EntityListITR.start(); EntityListITR.valid(); EntityListITR.forth() )
		if(EntityListITR.item()->GetName().compare(pName)==0)
		{
			mEntityList.remove(EntityListITR);
			return true;
		}

	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return false;
}

bool MEntity::moveTo ( const std::string &pName, const SGZ::VECTOR3 &pVector )
{
	/** Move to direct co-ordinates */
	IEntity* entity = getEntity(pName);
	if (entity) {
		entity->MoveTo(pVector);
		return true;
	}
	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return false;
}

bool MEntity::lookTo ( const std::string &pName, const SGZ::VECTOR3 &pVector )
{
	/** Direction to look at ( move towards ) */
	/** Move to direct co-ordinates */
	IEntity* entity = getEntity(pName);
	if (entity) {
		entity->LookTo(pVector);
		return true;
	}
	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return false;
}

bool MEntity::moveDelta ( const std::string &pName, const SGZ::VECTOR3 &pVector )
{
	/** Move to direct co-ordinates */
	IEntity* entity = getEntity(pName);
	if (entity) {
		entity->MoveDelta(pVector);
		return true;
	}

	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return false;
}

bool MEntity::scale ( const std::string &pName, const SGZ::SCALER pValue )
{
	/** Move to direct co-ordinates */
	IEntity* entity = getEntity(pName);
	if (entity) {
		entity->Scale(pValue);
		return true;
	}

	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return false;
}

bool MEntity::scaleXYZ ( const std::string &pName, const SGZ::VECTOR3 &pVector )
{
	IEntity* entity = getEntity(pName);
	if (entity) {
		entity->ScaleXYZ(pVector);
		return true;
	}

	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return false;
}


bool MEntity::rotate ( const std::string &pName, const SGZ::VECTOR3 &pVector )
{
	IEntity* entity = getEntity(pName);
	if (entity) {
		entity->Rotate(pVector);
		return true;
	}
	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return false;
}

bool MEntity::setMaxAccel ( const std::string &pName, const SGZ::SCALER pValue )
{
	IEntity* entity = getEntity(pName);
	if (entity) {
		entity->MaxAccel(pValue);
		return true;
	}

	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return false;
}

bool MEntity::setAccel ( const std::string &pName, const SGZ::SCALER pValue )
{
	IEntity* entity = getEntity(pName);
	if (entity) {
		entity->SetAccel(pValue);
		return true;
	}

	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return false;
}

bool MEntity::setDimensions ( const std::string &pName, const SGZ::VECTOR3 &pVector )
{
	IEntity* entity = getEntity(pName);
	if (entity) {
		entity->SetWidth(pVector.x);
		entity->SetHeight(pVector.y);
		entity->SetDepth(pVector.z);
		return true;
	}
	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return false;
}

bool MEntity::setMaxSpeed ( const std::string &pName, const SGZ::SCALER pValue )
{
	IEntity* entity = getEntity(pName);
	if (entity) {
		entity->MaxSpeed(pValue);
		return true;
	}

	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return false;
}

bool MEntity::setSpeed ( const std::string &pName, const SGZ::SCALER pValue )
{
	IEntity* entity = getEntity(pName);
	if (entity) {
		entity->SetSpeed(pValue);
		return true;
	}

	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return false;
}

bool MEntity::stop ( const std::string &pName )
{
	IEntity* entity = getEntity(pName);
	if (entity) {
		entity->Stop();
		return true;
	}

	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return false;
}

bool MEntity::setCollisionGeom ( const std::string &pName, const int pType )
{
   IEntity* entity = getEntity(pName);
	if (entity) {
		entity->SetCollisionGeom(pType);
		return true;
	}

	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return false;
}

bool MEntity::setAnimation( const std::string &pName, const std::string &pAnimName )
{
	IEntity* entity = getEntity(pName);
	if (entity) {
		entity->SetAnimation(pAnimName);
		return true;
	}

	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return false;
}

bool MEntity::createAnimation( const std::string &pName, const std::string &pAnimName )
{
	IEntity* entity = getEntity(pName);
	if (entity) {
		entity->CreateAnimation(pAnimName);
		return true;
	}

	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return false;
}

bool MEntity::deleteAnimation( const std::string &pName, const std::string &pAnimName )
{
	IEntity* entity = getEntity(pName);
	if (entity) {
		entity->DeleteAnimation(pAnimName);
		return true;
	}

	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return false;
}


bool MEntity::loadFrame ( const std::string &pName, const std::string &pAnimName, const std::string &pTexName, const std::string &pMaskName, const int pFrameDelay, const int pU, const int pV, const SGZ::RGBCOLOUR &pColourKey )
{
	IEntity* entity = getEntity(pName);
	if (entity) {
		entity->LoadFrame(pAnimName, pTexName, pMaskName, pFrameDelay, pU, pV, pColourKey);
		return true;
	}

	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return false;
}

SGZ::VECTOR3 MEntity::getPosition ( const std::string &pName )
{
	IEntity* entity = getEntity(pName);
	if (entity) {
		return SGZ::VECTOR3( entity->GetX(), entity->GetY(), entity->GetZ() );
	}

	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return SGZ::VECTOR3();
}

SGZ::VECTOR3 MEntity::getDimensions ( const std::string &pName )
{
	IEntity* entity = getEntity(pName);
	if (entity) {
		return SGZ::VECTOR3( entity->GetWidth(), entity->GetHeight(), entity->GetDepth() );
	}

	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return SGZ::VECTOR3();
}

SGZ::VECTOR3 MEntity::getLooking ( const std::string &pName )
{
	IEntity* entity = getEntity(pName);
	if (entity) {
		return SGZ::VECTOR3( entity->GetLookX(), entity->GetLookY(), entity->GetLookZ() );
	}

	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return SGZ::VECTOR3();
}

SGZ::SCALER MEntity::getSpeed ( const std::string &pName )
{
	IEntity* entity = getEntity(pName);
	if (entity) {
		return entity->GetSpeed();
	}

	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return 0;
}

SGZ::SCALER MEntity::getAccel ( const std::string &pName )
{
	IEntity* entity = getEntity(pName);
	if (entity) {
		return entity->GetAccel();
	}

	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return 0;
}

std::string MEntity::getAnimation( const std::string &pName )
{
	IEntity* entity = getEntity(pName);
	if (entity) {
		return entity->GetAnimation();
	}

	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return "none";
}

bool MEntity::setColour ( const std::string &pName, const SGZ::RGBCOLOUR &pColour )
{
	IEntity* entity = getEntity(pName);
	if (entity) {
		entity->Colour(pColour);
		return true;
	}

	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return false;
}

bool MEntity::changeColour( const std::string &pName, const SGZ::RGBCOLOUR &pOldColour, const SGZ::RGBCOLOUR &pNewColour)
{
	IEntity* entity = getEntity(pName);
	if (entity) {
		entity->ChangeColour(pOldColour, pNewColour);
		return true;
	}
	
	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return false;
}

bool MEntity::newVar ( const std::string &pName, const std::string &pVarName )
{
	IEntity* entity = getEntity(pName);
	if (entity) {
		entity->NewVar(pVarName);
		return true;
	}

	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return false;
}

bool MEntity::deleteVar ( const std::string &pName, const std::string &pVarName )
{
	IEntity* entity = getEntity(pName);
	if (entity) {
		entity->DeleteVar(pVarName);
		return true;
	}

	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return false;
}

bool MEntity::changeVar ( const std::string &pName, const std::string &pVarName, const std::string &pValue )
{
	IEntity* entity = getEntity(pName);
	if (entity) {
		entity->ChangeVar(pVarName, pValue);
		return true;
	}

	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return false;
}

std::string MEntity::checkVar ( const std::string &pName, const std::string &pVarName )
{
	IEntity* entity = getEntity(pName);
	if (entity) {
		return entity->CheckVar(pVarName);
	}

	Logger.log( SGZLOG::Warning, "Entity " + pName + " does not exist!\n");
	return "none";
}

