#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include <States/State.h>
#include <Resources/Resource.h>

class WorldManager;
class GameState : public GLESGAE::State
{
	public:
		/// Construct the State
		GameState();
		
		/// Update the State
		bool update(const float delta);
		
		/// Access the World Manager
		WorldManager* getWorldManager() const { return mWorldManager; }
		
		/// Tear down the State
		~GameState();
		
	protected:
		void loadTextures();
		void unloadTextures();
		
		void loadMeshes();
		void unloadMeshes();
		
		void loadWorld();
		
	private:
		GameState(const GameState&);
		GameState& operator=(const GameState&);
		
		WorldManager* mWorldManager;
};

#endif

