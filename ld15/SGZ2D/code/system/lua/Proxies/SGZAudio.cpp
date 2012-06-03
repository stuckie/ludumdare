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

#include "SGZAudio.h"

#include "../../../common/engine/CInterpret.h"
#include "../../../client/OClient.h"
#include "../../../client/audio/OAudio.h"

int SGZAudio_Proxy::LoadMUS(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->loadMUSFile(lua_tostring(Lua, -1), lua_tostring(Lua, -2));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::LoadSFX(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->loadSFXFile(lua_tostring(Lua, -1), lua_tostring(Lua, -2));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);;

	return 0;
}

int SGZAudio_Proxy::RemoveMUS(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->removeMUS(lua_tostring(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::RemoveSFX(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->removeSFX(lua_tostring(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::PlayMUS(lua_State *Lua)
{
	int values = lua_gettop(Lua);
	if (values>1)
		SGZ::Interpret.accessClient()->accessAudio()->playMUS(lua_tostring(Lua, -2), (int)lua_tonumber(Lua, -1));
	else
		SGZ::Interpret.accessClient()->accessAudio()->playMUS(lua_tostring(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::PlaySFX(lua_State *Lua)
{
	int values = lua_gettop(Lua);
	int tmp = 0;
	if(values>2)
		tmp = SGZ::Interpret.accessClient()->accessAudio()->playSFX(lua_tostring(Lua, -3), (int)lua_tonumber(Lua, -2), (int)lua_tonumber(Lua, -1));
	else if (values>1)
		tmp = SGZ::Interpret.accessClient()->accessAudio()->playSFX(lua_tostring(Lua, -2), (int)lua_tonumber(Lua, -1));
	else
		tmp = SGZ::Interpret.accessClient()->accessAudio()->playSFX(lua_tostring(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, tmp);

	return 1;
}

int SGZAudio_Proxy::FadeInMUS(lua_State *Lua)
{
	int values = lua_gettop(Lua);
	if(values>2)
		SGZ::Interpret.accessClient()->accessAudio()->fadeInMUS(lua_tostring(Lua, -3), (int)lua_tonumber(Lua, -2), (int)lua_tonumber(Lua, -1));
	else
		SGZ::Interpret.accessClient()->accessAudio()->fadeInMUS(lua_tostring(Lua, -2), (int)lua_tonumber(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::FadeInSFX(lua_State *Lua)
{
	int values = lua_gettop(Lua);
	int tmp = 0;
	if(values>3)
		tmp = SGZ::Interpret.accessClient()->accessAudio()->fadeInSFX(lua_tostring(Lua, -4), (int)lua_tonumber(Lua, -3), (int)lua_tonumber(Lua, -2), (int)lua_tonumber(Lua, -1));
	else if (values>2)
		tmp = SGZ::Interpret.accessClient()->accessAudio()->fadeInSFX(lua_tostring(Lua, -3), (int)lua_tonumber(Lua, -2), (int)lua_tonumber(Lua, -1));
	else
		tmp = SGZ::Interpret.accessClient()->accessAudio()->fadeInSFX(lua_tostring(Lua, -2), (int)lua_tonumber(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, tmp);

	return 1;
}

int SGZAudio_Proxy::FadeOutMUS(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->fadeOutMUS((int)lua_tonumber(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::FadeOutCHAN(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->fadeOutCHAN((int)lua_tonumber(Lua, -2), (int)lua_tonumber(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::StopMUS(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->stopMUS();

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::StopCHAN(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->stopCHAN((int)lua_tonumber(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::PauseMUS(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->pauseMUS();

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::PauseCHAN(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->pauseCHAN((int)lua_tonumber(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::ResumeMUS(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->resumeMUS();

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::ResumeCHAN(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->resumeCHAN((int)lua_tonumber(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::RewindMUS(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->rewindMUS();

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::SetMUSPOS(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->setMUSPOS((double)lua_tonumber(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::SetMUSVolume(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->setVolumeMUS((int)lua_tonumber(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}


int SGZAudio_Proxy::SetSFXVolume(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->setVolumeSFX(lua_tostring(Lua, -2), (int)lua_tonumber(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::CHANPlaying(lua_State *Lua)
{
	int channelinfo = SGZ::Interpret.accessClient()->accessAudio()->isCHANPlaying((int)lua_tonumber(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, channelinfo);

	return 1;
}

int SGZAudio_Proxy::MUSPlaying(lua_State *Lua)
{
	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, SGZ::Interpret.accessClient()->accessAudio()->isMUSPlaying());

	return 1;
}

int SGZAudio_Proxy::SetChannels(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->setChannels((int)lua_tonumber(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::SetPanning(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->setPanning((int)lua_tonumber(Lua, -3), (int)lua_tonumber(Lua, -2), (int)lua_tonumber(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::SetDistance(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->setDistance((int)lua_tonumber(Lua, -2), (int)lua_tonumber(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::SetPosition(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->setPosition((int)lua_tonumber(Lua, -3), (int)lua_tonumber(Lua, -2), (int)lua_tonumber(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::SetReverse(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->setReverseStereo((int)lua_tonumber(Lua, -2), lua_toboolean(Lua, -1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::Update(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->updateAudio();

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::CreateGROUP(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->createGROUP((int)lua_tonumber(Lua, 2), lua_tostring(Lua, 1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::ReserveCHANS(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->reserveCHANS((int)lua_tonumber(Lua, 1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::GroupCHAN(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->groupCHAN((int)lua_tonumber(Lua, 2), lua_tostring(Lua, 1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::GroupCHANS(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->groupCHANS((int)lua_tonumber(Lua, 2), (int)lua_tonumber(Lua, 3), lua_tostring(Lua, 1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::CountGROUP(lua_State *Lua)
{
	int temp = SGZ::Interpret.accessClient()->accessAudio()->countGROUP(lua_tostring(Lua, 1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);

	return 1;
}

int SGZAudio_Proxy::CHANinGROUP(lua_State *Lua)
{
	int temp = SGZ::Interpret.accessClient()->accessAudio()->CHANinGROUP(lua_tostring(Lua, 1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);
	return 1;
}

int SGZAudio_Proxy::OldestGROUP(lua_State *Lua)
{
	int temp = SGZ::Interpret.accessClient()->accessAudio()->oldestGROUP(lua_tostring(Lua, 1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);
	return 1;
}

int SGZAudio_Proxy::NewestGROUP(lua_State *Lua)
{
	int temp = SGZ::Interpret.accessClient()->accessAudio()->newestGROUP(lua_tostring(Lua, 1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);
	return 1;
}

int SGZAudio_Proxy::FadeGROUP(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->fadeGROUP(lua_tostring(Lua, 1), (int)lua_tonumber(Lua, 2));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::HaltGROUP(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->haltGROUP(lua_tostring(Lua, 1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZAudio_Proxy::RemoveGROUP(lua_State *Lua)
{
	SGZ::Interpret.accessClient()->accessAudio()->removeGROUP(lua_tostring(Lua, 1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

const char SGZAudio_Proxy::className[] = "SGZAudioMan";
Lunar<SGZAudio_Proxy>::RegType SGZAudio_Proxy::methods[] =
{
	{"loadMUS", &SGZAudio_Proxy::LoadMUS},
	{"loadSFX", &SGZAudio_Proxy::LoadSFX},
	{"removeMUS", &SGZAudio_Proxy::RemoveMUS},
	{"removeSFX", &SGZAudio_Proxy::RemoveSFX},
	{"playMUS", &SGZAudio_Proxy::PlayMUS},
	{"playSFX", &SGZAudio_Proxy::PlaySFX},
	{"fadeInMUS", &SGZAudio_Proxy::FadeInMUS},
	{"fadeInSFX", &SGZAudio_Proxy::FadeInSFX},
	{"fadeOutMUS", &SGZAudio_Proxy::FadeOutMUS},
	{"fadeOutCHAN", &SGZAudio_Proxy::FadeOutCHAN},
	{"stopMUS", &SGZAudio_Proxy::StopMUS},
	{"stopCHAN", &SGZAudio_Proxy::StopCHAN},
	{"pauseMUS", &SGZAudio_Proxy::PauseMUS},
	{"pauseCHAN", &SGZAudio_Proxy::PauseCHAN},
	{"resumeMUS", &SGZAudio_Proxy::ResumeMUS},
	{"resumeCHAN", &SGZAudio_Proxy::ResumeCHAN},
	{"rewindMUS", &SGZAudio_Proxy::RewindMUS},
	{"setMUSPOS", &SGZAudio_Proxy::SetMUSPOS},
	{"setMUSVolume", &SGZAudio_Proxy::SetMUSVolume},
	{"setSFXVolume", &SGZAudio_Proxy::SetSFXVolume},
	{"isMUSPlaying", &SGZAudio_Proxy::MUSPlaying},
	{"isCHANPlaying", &SGZAudio_Proxy::CHANPlaying},
	{"setChannels", &SGZAudio_Proxy::SetChannels},
	{"setPanning", &SGZAudio_Proxy::SetPanning},
	{"setPosition", &SGZAudio_Proxy::SetPosition},
	{"setDistance", &SGZAudio_Proxy::SetDistance},
	{"setReverse", &SGZAudio_Proxy::SetReverse},
	{"update", &SGZAudio_Proxy::Update},
	{"createGROUP", &SGZAudio_Proxy::CreateGROUP},
	{"reserveCHANS", &SGZAudio_Proxy::ReserveCHANS},
	{"groupCHAN", &SGZAudio_Proxy::GroupCHAN},
	{"groupCHANS", &SGZAudio_Proxy::GroupCHANS},
	{"countGROUP", &SGZAudio_Proxy::CountGROUP},
	{"CHANinGROUP", &SGZAudio_Proxy::CHANinGROUP},
	{"oldestGROUP", &SGZAudio_Proxy::OldestGROUP},
	{"newestGROUP", &SGZAudio_Proxy::NewestGROUP},
	{"fadeGROUP", &SGZAudio_Proxy::FadeGROUP},
	{"haltGROUP", &SGZAudio_Proxy::HaltGROUP},
	{"removeGROUP", &SGZAudio_Proxy::RemoveGROUP},
	{0,0}
};

