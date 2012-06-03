#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

#include "State.h"

class MenuState : public State
{
	public:
		MenuState();
		
		enum MenuPhase {
			START_MENU
		,	MAIN_MENU
		,	CONFIG_MENU
		,	GAME_MENU
		};

		void update(const float deltaTime);
		
		const MenuPhase getMenuPhase() const { return menuPhase_; }
		void setMenuPhase(const MenuPhase menuPhase) { menuPhase_ = menuPhase; }
		
	private:
		MenuPhase menuPhase_;

};

#endif
