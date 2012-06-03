#include "FrontendState.h"

#include <Platform/Application.h>
#include <Resources/ResourceManager.h>
#include <States/StateStack.h>

#include "../../Resources/States.h"

using namespace GLESGAE;

FrontendState::FrontendState()
:State(Fingers::States::FrontendState)
{
}

FrontendState::~FrontendState()
{
}

bool FrontendState::update(const float /*delta*/)
{
	
	return true;
}

