#include "GameState.h"

#include <Utils/HashString.h>

using namespace GLESGAE;

GameState::GameState()
: State(HashString("GameState"))
{
}

bool GameState::update(const float /*deltaTime*/)
{
	return true;
}

GameState::~GameState()
{
}

