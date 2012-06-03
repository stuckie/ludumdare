#include "WorldManager.h"

#include "WorldRooms.h"

using namespace GLESGAE;

WorldManager::WorldManager(const unsigned int floors)
: mRooms()
, mFloor(Fingers::Rooms::Floor1Id)
{
	for (unsigned int index(0U); index < floors; ++index)
		mRooms.push_back(std::vector<Resource<Room> >());
}

void WorldManager::addRoom(const GLESGAE::Resource<Room>& room)
{
	mRooms[room->getFloor()].push_back(room);
}

void WorldManager::render()
{
	const std::vector<Resource<Room> >& rooms(mRooms[mFloor]);
	for (std::vector<Resource<Room> >::const_iterator itr(rooms.begin()); itr < rooms.end(); ++itr) {
		if (true == (*itr)->isVisible())
			(*itr)->render();
	}
}

void WorldManager::update(const float delta)
{
	const std::vector<Resource<Room> >& rooms(mRooms[mFloor]);
	for (std::vector<Resource<Room> >::const_iterator itr(rooms.begin()); itr < rooms.end(); ++itr) {
		if (true == (*itr)->isVisible())
			(*itr)->update(delta);
	}
}

