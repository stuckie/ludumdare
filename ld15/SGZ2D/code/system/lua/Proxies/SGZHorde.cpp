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
	\file SGZHorde.cpp
	\brief The Horde Proxy Methods

*/


#include "../../../arch.h"
#if defined(REND_HORDE) || defined(REND_SDLHORDE)

#include "SGZODE.h"		 // to allow macro for accessing the physics engine
#include "SGZHorde.h"
#include "../../../common/engine/CInterpret.h"
#include "../../../common/debug/CDebug.h"
#include <string>
#include "utMath.h"

//#define THROW_PLAYER_POSITIONS

int SGZHorde_Proxy::GetResourcePath(lua_State *Lua)
{
	std::string tmp;
	std::string check = lua_tostring(Lua, 1);

	if (check.compare("SceneGraph")==0)
		tmp.insert(0, Horde3DUtils::getResourcePath(ResourceTypes::SceneGraph));
	else if (check.compare("Geometry")==0)
		tmp.insert(0, Horde3DUtils::getResourcePath(ResourceTypes::Geometry));
	else if (check.compare("Animation")==0)
		tmp.insert(0, Horde3DUtils::getResourcePath(ResourceTypes::Animation));
	else if (check.compare("Material")==0)
		tmp.insert(0, Horde3DUtils::getResourcePath(ResourceTypes::Material));
	else if (check.compare("Code")==0)
		tmp.insert(0, Horde3DUtils::getResourcePath(ResourceTypes::Code));
	else if (check.compare("Shader")==0)
		tmp.insert(0, Horde3DUtils::getResourcePath(ResourceTypes::Shader));
	else if (check.compare("Texture2D")==0)
		tmp.insert(0, Horde3DUtils::getResourcePath(ResourceTypes::Texture2D));
	else if (check.compare("TextureCube")==0)
		tmp.insert(0, Horde3DUtils::getResourcePath(ResourceTypes::TextureCube));
	else if (check.compare("Effect")==0)
		tmp.insert(0, Horde3DUtils::getResourcePath(ResourceTypes::Effect));
	else if (check.compare("Pipeline")==0)
		tmp.insert(0, Horde3DUtils::getResourcePath(ResourceTypes::Pipeline));
	else
		Logger.log( SGZLOG::Warning, "Trying to get Unknown Resource Path.\n");

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushstring(Lua, tmp.c_str());

	return 1;
}

int SGZHorde_Proxy::SetResourcePath(lua_State *Lua)
{
	std::string check = lua_tostring(Lua, 1);

	if (check.compare("SceneGraph")==0)
		Horde3DUtils::setResourcePath(ResourceTypes::SceneGraph, lua_tostring(Lua, 2));
	else if (check.compare("Geometry")==0)
		Horde3DUtils::setResourcePath(ResourceTypes::Geometry, lua_tostring(Lua, 2));
	else if (check.compare("Animation")==0)
		Horde3DUtils::setResourcePath(ResourceTypes::Animation, lua_tostring(Lua, 2));
	else if (check.compare("Material")==0)
		Horde3DUtils::setResourcePath(ResourceTypes::Material, lua_tostring(Lua, 2));
	else if (check.compare("Code")==0)
		Horde3DUtils::setResourcePath(ResourceTypes::Code, lua_tostring(Lua, 2));
	else if (check.compare("Shader")==0)
		Horde3DUtils::setResourcePath(ResourceTypes::Shader, lua_tostring(Lua, 2));
	else if (check.compare("Texture2D")==0)
		Horde3DUtils::setResourcePath(ResourceTypes::Texture2D, lua_tostring(Lua, 2));
	else if (check.compare("TextureCube")==0)
		Horde3DUtils::setResourcePath(ResourceTypes::TextureCube, lua_tostring(Lua, 2));
	else if (check.compare("Effect")==0)
		Horde3DUtils::setResourcePath(ResourceTypes::Effect, lua_tostring(Lua, 2));
	else if (check.compare("Pipeline")==0)
		Horde3DUtils::setResourcePath(ResourceTypes::Pipeline, lua_tostring(Lua, 2));
	else
		Logger.log( SGZLOG::Warning, "Trying to Set Unknown Resource Path.\n");

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZHorde_Proxy::LoadResourcesFromDisk(lua_State *Lua)
{
	Horde3DUtils::loadResourcesFromDisk(lua_tostring(Lua, 1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZHorde_Proxy::PickNode(lua_State *Lua)
{

	int tmp = Horde3DUtils::pickNode( Horde3D::findNodes( RootNode, lua_tostring(Lua, 1), SceneNodeTypes::Camera ), (float)lua_tonumber(Lua, 2), (float)lua_tonumber(Lua, 3));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, tmp);

	return 1;
}

int SGZHorde_Proxy::ShowText(lua_State *Lua)
{
	Horde3DUtils::showText(lua_tostring(Lua, 1), (float)lua_tonumber(Lua, 2), (float)lua_tonumber(Lua, 3), (float)lua_tonumber(Lua, 4), (int)lua_tonumber(Lua, 5),
						   (ResHandle)lua_tonumber(Lua, 6));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZHorde_Proxy::FrameInfo(lua_State *Lua)
{
	Horde3DUtils::showFrameStats( (ResHandle)lua_tonumber(Lua, 1), (float)SGZ::Interpret.accessServer()->World()->getFps() );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZHorde_Proxy::GetStats(lua_State *Lua)
{

	float temp = 0;
	std::string check = lua_tostring(Lua, 1);

	if (check.compare("TriCount")==0)
		temp = Horde3D::getStat( EngineStats::TriCount, (bool)lua_toboolean(Lua, 2) );
	else if (check.compare("BatchCount")==0)
		temp = Horde3D::getStat( EngineStats::BatchCount, (bool)lua_toboolean(Lua, 2) );
	else if (check.compare("LightPassCount")==0)
		temp = Horde3D::getStat( EngineStats::LightPassCount, (bool)lua_toboolean(Lua, 2) );
	else
		temp = 0;

	lua_pushnumber(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::SetOption(lua_State *Lua)
{
	std::string check = lua_tostring(Lua, 1);

	if (check.compare("MaxLogLevel")==0)
		Horde3D::setOption( EngineOptions::MaxLogLevel, (float)lua_tonumber(Lua, 2));
	if (check.compare("TrilinearFiltering")==0)
		Horde3D::setOption( EngineOptions::TrilinearFiltering, (float)lua_tonumber(Lua, 2));
	if (check.compare("AnisotropyFactor")==0)
		Horde3D::setOption( EngineOptions::AnisotropyFactor, (float)lua_tonumber(Lua, 2));
	if (check.compare("TexCompression")==0)
		Horde3D::setOption( EngineOptions::TexCompression, (float)lua_tonumber(Lua, 2));
	if (check.compare("LoadTextures")==0)
		Horde3D::setOption( EngineOptions::LoadTextures, (float)lua_tonumber(Lua, 2));
	if (check.compare("FastAnimation")==0)
		Horde3D::setOption( EngineOptions::FastAnimation, (float)lua_tonumber(Lua, 2));
	if (check.compare("ShadowMapSize")==0)
		Horde3D::setOption( EngineOptions::ShadowMapSize, (float)lua_tonumber(Lua, 2));
	if (check.compare("SampleCount")==0)
		Horde3D::setOption( EngineOptions::SampleCount, (float)lua_tonumber(Lua, 2));
	if (check.compare("WireframeMode")==0)
		Horde3D::setOption( EngineOptions::WireframeMode, (float)lua_tonumber(Lua, 2));
	if (check.compare("DebugViewMode")==0)
		Horde3D::setOption( EngineOptions::DebugViewMode, (float)lua_tonumber(Lua, 2));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZHorde_Proxy::AddResource(lua_State *Lua)
{
	std::string check = lua_tostring(Lua, 1);

	ResHandle temp = 0;

	if (check.compare("SceneGraph")==0)
		temp = Horde3D::addResource( ResourceTypes::SceneGraph, lua_tostring(Lua, 2), 0 );
	else if (check.compare("Geometry")==0)
		temp = Horde3D::addResource( ResourceTypes::Geometry, lua_tostring(Lua, 2), 0 );
	else if (check.compare("Animation")==0)
		temp = Horde3D::addResource( ResourceTypes::Animation, lua_tostring(Lua, 2), 0 );
	else if (check.compare("Material")==0)
		temp = Horde3D::addResource( ResourceTypes::Material, lua_tostring(Lua, 2), 0 );
	else if (check.compare("Code")==0)
		temp = Horde3D::addResource( ResourceTypes::Code, lua_tostring(Lua, 2), 0 );
	else if (check.compare("Shader")==0)
		temp = Horde3D::addResource( ResourceTypes::Shader, lua_tostring(Lua, 2), 0 );
	else if (check.compare("Texture2D")==0)
		temp = Horde3D::addResource( ResourceTypes::Texture2D, lua_tostring(Lua, 2), 0 );
	else if (check.compare("TextureCube")==0)
		temp = Horde3D::addResource( ResourceTypes::TextureCube, lua_tostring(Lua, 2), 0 );
	else if (check.compare("Effect")==0)
		temp = Horde3D::addResource( ResourceTypes::Effect, lua_tostring(Lua, 2), 0 );
	else if (check.compare("Pipeline")==0)
		temp = Horde3D::addResource( ResourceTypes::Pipeline, lua_tostring(Lua, 2), 0 );
	else
		Logger.log( SGZLOG::Warning, "Trying to Set Unknown Resource Path.\n");

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::Version(lua_State *Lua)
{

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushstring(Lua, Horde3D::getVersionString());

	return 1;
}

int SGZHorde_Proxy::CheckForExtension(lua_State *Lua)
{

	bool temp = Horde3D::checkExtension(lua_tostring(Lua, 1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::EmptySceneGraph(lua_State *Lua)
{

	Horde3D::clear();

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZHorde_Proxy::GetMessage(lua_State *Lua)
{
	int level = (int)lua_tonumber(Lua, 1);
	float time = (float)lua_tonumber(Lua, 2);

	std::string temp = Horde3D::getMessage(&level, &time);

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushstring(Lua, temp.c_str());

	return 1;
}

int SGZHorde_Proxy::GetOption(lua_State *Lua)
{

	std::string check = lua_tostring(Lua, 1);
	float temp = 0;

	if (check.compare("MaxLogLevel")==0)
		temp = Horde3D::getOption( EngineOptions::MaxLogLevel );
	if (check.compare("TrilinearFiltering")==0)
		temp = Horde3D::getOption( EngineOptions::TrilinearFiltering );
	if (check.compare("AnisotropyFactor")==0)
		temp = Horde3D::getOption( EngineOptions::AnisotropyFactor );
	if (check.compare("TexCompression")==0)
		temp = Horde3D::getOption( EngineOptions::TexCompression );
	if (check.compare("LoadTextures")==0)
		temp = Horde3D::getOption( EngineOptions::LoadTextures );
	if (check.compare("FastAnimation")==0)
		temp = Horde3D::getOption( EngineOptions::FastAnimation );
	if (check.compare("ShadowMapSize")==0)
		temp = Horde3D::getOption( EngineOptions::ShadowMapSize );
	if (check.compare("SampleCount")==0)
		temp = Horde3D::getOption( EngineOptions::SampleCount );
	if (check.compare("WireframeMode")==0)
		temp = Horde3D::getOption( EngineOptions::WireframeMode );
	if (check.compare("DebugViewMode")==0)
		temp = Horde3D::getOption( EngineOptions::DebugViewMode );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::ShowOverlay(lua_State *Lua)
{

	Horde3D::showOverlay(   (float)lua_tonumber(Lua, 1), (float)lua_tonumber(Lua, 2), (float)lua_tonumber(Lua, 3), (float)lua_tonumber(Lua, 4),
							(float)lua_tonumber(Lua, 5), (float)lua_tonumber(Lua, 6), (float)lua_tonumber(Lua, 7), (float)lua_tonumber(Lua, 8),
							(float)lua_tonumber(Lua, 9), (float)lua_tonumber(Lua,10), (float)lua_tonumber(Lua,11), (float)lua_tonumber(Lua,12),
							(float)lua_tonumber(Lua,13), (float)lua_tonumber(Lua,14), (float)lua_tonumber(Lua,15), (float)lua_tonumber(Lua,16),
							(int)lua_tonumber(Lua,17), (ResHandle)lua_tonumber(Lua, 18));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZHorde_Proxy::ClearOverlays(lua_State *Lua)
{

	Horde3D::clearOverlays();

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZHorde_Proxy::GetResourceType(lua_State *Lua)
{
	std::string tmp;

	if (Horde3D::getResourceType((ResHandle)lua_tonumber(Lua, 1))==ResourceTypes::SceneGraph)
		tmp.insert(0,"SceneGraph");
	else if (Horde3D::getResourceType((ResHandle)lua_tonumber(Lua, 1))==ResourceTypes::Geometry)
		tmp.insert(0,"Geometry");
	else if (Horde3D::getResourceType((ResHandle)lua_tonumber(Lua, 1))==ResourceTypes::Animation)
		tmp.insert(0,"Animation");
	else if (Horde3D::getResourceType((ResHandle)lua_tonumber(Lua, 1))==ResourceTypes::Material)
		tmp.insert(0,"Material");
	else if (Horde3D::getResourceType((ResHandle)lua_tonumber(Lua, 1))==ResourceTypes::Code)
		tmp.insert(0,"Code");
	else if (Horde3D::getResourceType((ResHandle)lua_tonumber(Lua, 1))==ResourceTypes::Shader)
		tmp.insert(0,"Shader");
	else if (Horde3D::getResourceType((ResHandle)lua_tonumber(Lua, 1))==ResourceTypes::Texture2D)
		tmp.insert(0,"Texture2D");
	else if (Horde3D::getResourceType((ResHandle)lua_tonumber(Lua, 1))==ResourceTypes::TextureCube)
		tmp.insert(0,"TextureCube");
	else if (Horde3D::getResourceType((ResHandle)lua_tonumber(Lua, 1))==ResourceTypes::Effect)
		tmp.insert(0,"Effect");
	else if (Horde3D::getResourceType((ResHandle)lua_tonumber(Lua, 1))==ResourceTypes::Pipeline)
		tmp.insert(0,"Pipeline");
	else
		Logger.log( SGZLOG::Warning, "Unknown Resource Type.\n");

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushstring(Lua, tmp.c_str());

	return 1;
}

int SGZHorde_Proxy::GetResourceName(lua_State *Lua)
{
	std::string tmp = Horde3D::getResourceName((ResHandle)lua_tonumber(Lua, 1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushstring(Lua, tmp.c_str());

	return 1;
}

int SGZHorde_Proxy::FindResource(lua_State *Lua)
{

	std::string check = lua_tostring(Lua, 1);
	ResHandle temp = 0;

	if (check.compare("SceneGraph")==0)
		temp = Horde3D::findResource( ResourceTypes::SceneGraph, lua_tostring(Lua, 2) );
	else if (check.compare("Geometry")==0)
		temp = Horde3D::findResource( ResourceTypes::Geometry, lua_tostring(Lua, 2) );
	else if (check.compare("Animation")==0)
		temp = Horde3D::findResource( ResourceTypes::Animation, lua_tostring(Lua, 2) );
	else if (check.compare("Material")==0)
		temp = Horde3D::findResource( ResourceTypes::Material, lua_tostring(Lua, 2) );
	else if (check.compare("Code")==0)
		temp = Horde3D::findResource( ResourceTypes::Code, lua_tostring(Lua, 2) );
	else if (check.compare("Shader")==0)
		temp = Horde3D::findResource( ResourceTypes::Shader, lua_tostring(Lua, 2) );
	else if (check.compare("Texture2D")==0)
		temp = Horde3D::findResource( ResourceTypes::Texture2D, lua_tostring(Lua, 2) );
	else if (check.compare("TextureCube")==0)
		temp = Horde3D::findResource( ResourceTypes::TextureCube, lua_tostring(Lua, 2) );
	else if (check.compare("Effect")==0)
		temp = Horde3D::findResource( ResourceTypes::Effect, lua_tostring(Lua, 2) );
	else if (check.compare("Pipeline")==0)
		temp = Horde3D::findResource( ResourceTypes::Pipeline, lua_tostring(Lua, 2) );
	else
		Logger.log( SGZLOG::Warning, "Unknown Resource Type.\n");

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::CloneResource(lua_State *Lua)
{

	ResHandle temp = Horde3D::cloneResource( (ResHandle)lua_tonumber(Lua, 1), lua_tostring(Lua, 2) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::RemoveResource(lua_State *Lua)
{

	int temp = Horde3D::removeResource((ResHandle)lua_tonumber(Lua, 1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::LoadResource(lua_State *Lua)
{

	bool temp = Horde3D::loadResource( (ResHandle)lua_tonumber(Lua, 1), lua_tostring(Lua, 2), (int)lua_tonumber(Lua, 3) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::UnloadResource(lua_State *Lua)
{

	bool temp = Horde3D::unloadResource( (ResHandle)lua_tonumber(Lua, 1) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::GetResourceParamInt(lua_State *Lua)
{

	int temp = Horde3D::getResourceParami( (ResHandle)lua_tonumber(Lua, 1), (int)lua_tonumber(Lua, 2) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::GetResourceParamFloat(lua_State *Lua)
{
	float temp = Horde3D::getResourceParamf( (ResHandle)lua_tonumber(Lua, 1), (int)lua_tonumber(Lua, 2) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::GetResourceData(lua_State *Lua)
{

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZHorde_Proxy::UpdateResourceData(lua_State *Lua)
{

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZHorde_Proxy::QueryUnloadedResources(lua_State *Lua)
{
	lua_pushnumber(Lua, Horde3D::queryUnloadedResource((int)lua_tonumber(Lua, 1)));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 1;
}

int SGZHorde_Proxy::ReleaseUnusedResources(lua_State *Lua)
{

	Horde3D::releaseUnusedResources();

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZHorde_Proxy::Create2DTexture(lua_State *Lua)
{

	int temp = Horde3D::createTexture2D(lua_tostring(Lua, 1), (int)lua_tonumber(Lua, 2), (int)lua_tonumber(Lua, 3), (int)lua_tonumber(Lua, 4), lua_toboolean(Lua, 5));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::SetShaderPreambles(lua_State *Lua)
{

	Horde3D::setShaderPreambles(lua_tostring(Lua, 1), lua_tostring(Lua, 2));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZHorde_Proxy::SetMaterialUniform(lua_State *Lua)
{
	bool temp = Horde3D::setMaterialUniform( (ResHandle)lua_tonumber(Lua, 1), lua_tostring(Lua, 2), (float)lua_tonumber(Lua, 3), (float)lua_tonumber(Lua, 4), (float)lua_tonumber(Lua, 5), (float)lua_tonumber(Lua, 6) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::SetPipelineStageActivation(lua_State *Lua)
{

	bool temp = Horde3D::setPipelineStageActivation(  (ResHandle)lua_tonumber(Lua, 1), lua_tostring(Lua, 2), lua_toboolean(Lua, 3) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::GetPipelineRenderTargetData(lua_State *Lua)
{

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZHorde_Proxy::Render(lua_State *Lua)
{

	Horde3D::render((NodeHandle)lua_tonumber(Lua, 1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZHorde_Proxy::Resize(lua_State *Lua)
{
	Horde3D::resize((int)lua_tonumber(Lua, 1), (int)lua_tonumber(Lua, 2), (int)lua_tonumber(Lua, 3), (int)lua_tonumber(Lua, 4));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZHorde_Proxy::AddNodes(lua_State *Lua)
{
	NodeHandle Node = 0;
	if (lua_tonumber(Lua, 1) == 0)
		Node = RootNode;
	else Node = (NodeHandle)lua_tonumber(Lua, 1);

	NodeHandle temp = Horde3D::addNodes( Node, (ResHandle)lua_tonumber(Lua, 2) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::AddCameraNode(lua_State *Lua)
{
	NodeHandle Node = 0;
	if (lua_tonumber(Lua, 1) == 0)
		Node = RootNode;
	else Node = (NodeHandle)lua_tonumber(Lua, 1);
	NodeHandle temp = Horde3D::addCameraNode( Node, lua_tostring(Lua, 2), (ResHandle)lua_tonumber(Lua, 3) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::GetNodeType(lua_State *Lua)
{
	int temp = Horde3D::getNodeType( (NodeHandle)lua_tonumber(Lua, 1) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	if (temp==SceneNodeTypes::Camera)
		lua_pushstring(Lua, "Camera");
	else if (temp==SceneNodeTypes::Emitter)
		lua_pushstring(Lua, "Emitter");
	else if (temp==SceneNodeTypes::Group)
		lua_pushstring(Lua, "Group");
	else if (temp==SceneNodeTypes::Joint)
		lua_pushstring(Lua, "Joint");
	else if (temp==SceneNodeTypes::Light)
		lua_pushstring(Lua, "Light");
	else if (temp==SceneNodeTypes::Mesh)
		lua_pushstring(Lua, "Mesh");
	else if (temp==SceneNodeTypes::Model)
		lua_pushstring(Lua, "Model");
	else lua_pushstring(Lua, "Undefined");

	return 1;
}

int SGZHorde_Proxy::GetNodeName(lua_State *Lua)
{
	//std::string temp = Horde3D::getNodeName((NodeHandle)lua_tonumber(Lua, 1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

//	lua_pushstring(Lua, temp.c_str());

	return 1;
}

int SGZHorde_Proxy::SetNodeName(lua_State *Lua)
{

//	bool temp = Horde3D::setNodeName((NodeHandle)lua_tonumber(Lua, 1), lua_tostring(Lua, 2));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

//	lua_pushboolean(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::GetNodeParent(lua_State *Lua)
{

	NodeHandle temp = Horde3D::getNodeParent((NodeHandle)lua_tonumber(Lua, 1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::SetNodeParent(lua_State *Lua)
{

	bool temp = Horde3D::setNodeParent((NodeHandle)lua_tonumber(Lua, 1), (NodeHandle)lua_tonumber(Lua, 2));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::GetNodeChild(lua_State *Lua)
{
	NodeHandle temp = Horde3D::getNodeChild((NodeHandle)lua_tonumber(Lua, 1), (int)lua_tonumber(Lua, 2));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::GetNodeAttachmentString(lua_State *Lua)
{
//	std::string temp = Horde3D::getNodeAttachmentString((NodeHandle)lua_tonumber(Lua, 1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

//	lua_pushstring(Lua, temp.c_str());

	return 1;
}

int SGZHorde_Proxy::RemoveNodes(lua_State *Lua)
{
	bool temp = Horde3D::removeNode((NodeHandle)lua_tonumber(Lua, 1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::SetNodeActivation(lua_State *Lua)
{
	bool temp = Horde3D::setNodeActivation((NodeHandle)lua_tonumber(Lua, 1), lua_toboolean(Lua, 2));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::CheckNodeTransformFlag(lua_State *Lua)
{

	bool temp = Horde3D::checkNodeTransformFlag((NodeHandle)lua_tonumber(Lua, 1), lua_toboolean(Lua, 2));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::GetNodeTransform(lua_State *Lua)
{
	SGZ::VECTOR3 pos, rot, scale;

	Horde3D::getNodeTransform((NodeHandle)lua_tonumber(Lua, 1), &pos.x,  &pos.y,  &pos.z,  &rot.x,  &rot.y,  &rot.z,  &scale.x,  &scale.y,  &scale.z);

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, pos.x);
	lua_pushnumber(Lua, pos.y);
	lua_pushnumber(Lua, pos.z);

	lua_pushnumber(Lua, rot.x);
	lua_pushnumber(Lua, rot.y);
	lua_pushnumber(Lua, rot.z);

	lua_pushnumber(Lua, scale.x);
	lua_pushnumber(Lua, scale.y);
	lua_pushnumber(Lua, scale.z);

	return 9;
}

int SGZHorde_Proxy::SetNodeTransform(lua_State *Lua)
{

	bool temp = Horde3D::setNodeTransform(  (NodeHandle)lua_tonumber(Lua, 1),
											(float)lua_tonumber(Lua, 2), (float)lua_tonumber(Lua, 3), (float)lua_tonumber(Lua, 4),
											(float)lua_tonumber(Lua, 5), (float)lua_tonumber(Lua, 6), (float)lua_tonumber(Lua, 7),
											(float)lua_tonumber(Lua, 8), (float)lua_tonumber(Lua, 9), (float)lua_tonumber(Lua,10) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::GetNodeTransformMatrices(lua_State *Lua)
{

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZHorde_Proxy::SetNodeTransformMatrices(lua_State *Lua)
{

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZHorde_Proxy::GetNodeParamFloat(lua_State *Lua)
{

	float temp = Horde3D::getNodeParamf((NodeHandle)lua_tonumber(Lua, 1), (int)lua_tonumber(Lua, 2));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::SetNodeParamFloat(lua_State *Lua)
{
	bool temp = false;
	std::string check = lua_tostring(Lua, 2);

	if (check.compare("MinDist")==0)
		temp = Horde3D::setNodeParamf((NodeHandle)lua_tonumber(Lua, 1), GroupNodeParams::MinDist ,(float)lua_tonumber(Lua, 3));
	if (check.compare("MaxDist")==0)
		temp = Horde3D::setNodeParamf((NodeHandle)lua_tonumber(Lua, 1), GroupNodeParams::MaxDist ,(float)lua_tonumber(Lua, 3));
	if (check.compare("Radius")==0)
		temp = Horde3D::setNodeParamf((NodeHandle)lua_tonumber(Lua, 1), LightNodeParams::Radius ,(float)lua_tonumber(Lua, 3));
	if (check.compare("FOV")==0)
		temp = Horde3D::setNodeParamf((NodeHandle)lua_tonumber(Lua, 1), LightNodeParams::FOV ,(float)lua_tonumber(Lua, 3));
	if (check.compare("Col_R")==0)
		temp = Horde3D::setNodeParamf((NodeHandle)lua_tonumber(Lua, 1), LightNodeParams::Col_R ,(float)lua_tonumber(Lua, 3));
	if (check.compare("Col_G")==0)
		temp = Horde3D::setNodeParamf((NodeHandle)lua_tonumber(Lua, 1), LightNodeParams::Col_G ,(float)lua_tonumber(Lua, 3));
	if (check.compare("Col_B")==0)
		temp = Horde3D::setNodeParamf((NodeHandle)lua_tonumber(Lua, 1), LightNodeParams::Col_B ,(float)lua_tonumber(Lua, 3));
	if (check.compare("ShadowSplitLambda")==0)
		temp = Horde3D::setNodeParamf((NodeHandle)lua_tonumber(Lua, 1), LightNodeParams::ShadowSplitLambda ,(float)lua_tonumber(Lua, 3));
	if (check.compare("ShadowMapBias")==0)
		temp = Horde3D::setNodeParamf((NodeHandle)lua_tonumber(Lua, 1), LightNodeParams::ShadowMapBias ,(float)lua_tonumber(Lua, 3));
	if (check.compare("LeftPlane")==0)
		temp = Horde3D::setNodeParamf((NodeHandle)lua_tonumber(Lua, 1), CameraNodeParams::LeftPlane ,(float)lua_tonumber(Lua, 3));
	if (check.compare("RightPlane")==0)
		temp = Horde3D::setNodeParamf((NodeHandle)lua_tonumber(Lua, 1), CameraNodeParams::RightPlane ,(float)lua_tonumber(Lua, 3));
	if (check.compare("BottomPlane")==0)
		temp = Horde3D::setNodeParamf((NodeHandle)lua_tonumber(Lua, 1), CameraNodeParams::BottomPlane ,(float)lua_tonumber(Lua, 3));
	if (check.compare("TopPlane")==0)
		temp = Horde3D::setNodeParamf((NodeHandle)lua_tonumber(Lua, 1), CameraNodeParams::TopPlane ,(float)lua_tonumber(Lua, 3));
	if (check.compare("NearPlane")==0)
		temp = Horde3D::setNodeParamf((NodeHandle)lua_tonumber(Lua, 1), CameraNodeParams::NearPlane ,(float)lua_tonumber(Lua, 3));
	if (check.compare("FarPlane")==0)
		temp = Horde3D::setNodeParamf((NodeHandle)lua_tonumber(Lua, 1), CameraNodeParams::FarPlane ,(float)lua_tonumber(Lua, 3));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::GetNodeParamInt(lua_State *Lua)
{

	int temp = Horde3D::getNodeParami((NodeHandle)lua_tonumber(Lua, 1), (int)lua_tonumber(Lua, 2));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::SetNodeParamInt(lua_State *Lua)
{

	bool temp = false;
	std::string check = lua_tostring(Lua, 2);

	if (check.compare("GeometryRes")==0)
		temp = Horde3D::setNodeParami((NodeHandle)lua_tonumber(Lua, 1), ModelNodeParams::GeometryRes ,(int)lua_tonumber(Lua, 3));
	if (check.compare("SoftwareSkinning")==0)
		temp = Horde3D::setNodeParami((NodeHandle)lua_tonumber(Lua, 1), ModelNodeParams::SoftwareSkinning ,(int)lua_tonumber(Lua, 3));
	if (check.compare("MeshMaterialRes")==0)
		temp = Horde3D::setNodeParami((NodeHandle)lua_tonumber(Lua, 1), MeshNodeParams::MaterialRes ,(ResHandle)lua_tonumber(Lua, 3));
	if (check.compare("LightMaterialRes")==0)
		temp = Horde3D::setNodeParami((NodeHandle)lua_tonumber(Lua, 1), LightNodeParams::MaterialRes ,(ResHandle)lua_tonumber(Lua, 3));
	if (check.compare("EmitterMaterialRes")==0)
		temp = Horde3D::setNodeParami((NodeHandle)lua_tonumber(Lua, 1), EmitterNodeParams::MaterialRes ,(ResHandle)lua_tonumber(Lua, 3));
	if (check.compare("BatchStart")==0)
		temp = Horde3D::setNodeParami((NodeHandle)lua_tonumber(Lua, 1), MeshNodeParams::BatchStart ,(int)lua_tonumber(Lua, 3));
	if (check.compare("BatchCount")==0)
		temp = Horde3D::setNodeParami((NodeHandle)lua_tonumber(Lua, 1), MeshNodeParams::BatchCount ,(int)lua_tonumber(Lua, 3));
	if (check.compare("VertRStart")==0)
		temp = Horde3D::setNodeParami((NodeHandle)lua_tonumber(Lua, 1), MeshNodeParams::VertRStart ,(int)lua_tonumber(Lua, 3));
	if (check.compare("VertREnd")==0)
		temp = Horde3D::setNodeParami((NodeHandle)lua_tonumber(Lua, 1), MeshNodeParams::VertREnd ,(int)lua_tonumber(Lua, 3));
	if (check.compare("JointIndex")==0)
		temp = Horde3D::setNodeParami((NodeHandle)lua_tonumber(Lua, 1), JointNodeParams::JointIndex ,(int)lua_tonumber(Lua, 3));
	if (check.compare("PipelineRes")==0)
		temp = Horde3D::setNodeParami((NodeHandle)lua_tonumber(Lua, 1), CameraNodeParams::PipelineRes ,(int)lua_tonumber(Lua, 3));
	if (check.compare("OutputTex")==0)
		temp = Horde3D::setNodeParami((NodeHandle)lua_tonumber(Lua, 1), CameraNodeParams::OutputTex ,(int)lua_tonumber(Lua, 3));
	if (check.compare("OutputBufferIndex")==0)
		temp = Horde3D::setNodeParami((NodeHandle)lua_tonumber(Lua, 1), CameraNodeParams::OutputBufferIndex ,(int)lua_tonumber(Lua, 3));
	if (check.compare("Orthographic")==0)
		temp = Horde3D::setNodeParami((NodeHandle)lua_tonumber(Lua, 1), CameraNodeParams::Orthographic ,(int)lua_tonumber(Lua, 3));
	if (check.compare("OcclusionCulling")==0)
		temp = Horde3D::setNodeParami((NodeHandle)lua_tonumber(Lua, 1), CameraNodeParams::OcclusionCulling ,(int)lua_tonumber(Lua, 3));
	if (check.compare("ShadowMapCount")==0)
		temp = Horde3D::setNodeParami((NodeHandle)lua_tonumber(Lua, 1), LightNodeParams::ShadowMapCount ,(int)lua_tonumber(Lua, 3));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZHorde_Proxy::GetNodeAABB(lua_State *Lua)
{

	SGZ::VECTOR3 min, max;

	Horde3D::getNodeAABB((NodeHandle)lua_tonumber(Lua, 1), &min.x, &min.y, &min.z, &max.x, &max.y, &max.z);

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, min.x);
	lua_pushnumber(Lua, min.y);
	lua_pushnumber(Lua, min.z);

	lua_pushnumber(Lua, max.x);
	lua_pushnumber(Lua, max.y);
	lua_pushnumber(Lua, max.z);

	return 6;
}

int SGZHorde_Proxy::FindNodes(lua_State *Lua)
{
	int tmp = SceneNodeTypes::Undefined;
	std::string check = lua_tostring(Lua, 3);

	if (check.compare("Camera")==0)
		tmp = SceneNodeTypes::Camera;
	else if (check.compare("Emitter")==0)
		tmp = SceneNodeTypes::Emitter;
	else if (check.compare("Group")==0)
		tmp = SceneNodeTypes::Group;
	else if (check.compare("Joint")==0)
		tmp = SceneNodeTypes::Joint;
	else if (check.compare("Light")==0)
		tmp = SceneNodeTypes::Light;
	else if (check.compare("Mesh")==0)
		tmp = SceneNodeTypes::Mesh;
	else if (check.compare("Model")==0)
		tmp = SceneNodeTypes::Model;
	else
		Logger.log( SGZLOG::Warning, "Trying to find Unknown Resource.\n");

	NodeHandle node = (int)lua_tonumber(Lua, 1);
	if (node == 0) node = RootNode;
	int temp = Horde3D::findNodes(node, lua_tostring(Lua, 2), tmp);

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::GetNodeFindResult(lua_State *Lua)
{

	NodeHandle temp = Horde3D::getNodeFindResult((int)lua_tonumber(Lua, 1));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::CastRay(lua_State *Lua)
{

	NodeHandle temp = Horde3D::castRay((NodeHandle)lua_tonumber(Lua, 1),	(float)lua_tonumber(Lua, 2), (float)lua_tonumber(Lua, 3), (float)lua_tonumber(Lua, 4),
									   (float)lua_tonumber(Lua, 5), (float)lua_tonumber(Lua, 6), (float)lua_tonumber(Lua, 7), (int)lua_tonumber(Lua, 8));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::AddGroupNode(lua_State *Lua)
{

	NodeHandle temp = Horde3D::addGroupNode((NodeHandle)lua_tonumber(Lua, 1), lua_tostring(Lua, 2));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::AddModelNode(lua_State *Lua)
{

	NodeHandle temp = Horde3D::addModelNode((NodeHandle)lua_tonumber(Lua, 1), lua_tostring(Lua, 2), (ResHandle)lua_tonumber(Lua, 3));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::SetupModelAnimStage(lua_State *Lua)
{

	bool temp = Horde3D::setupModelAnimStage((NodeHandle)lua_tonumber(Lua, 1), (int)lua_tonumber(Lua, 2), (ResHandle)lua_tonumber(Lua, 3), lua_tostring(Lua, 4), lua_toboolean(Lua, 5));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::SetModelAnimParams(lua_State *Lua)
{

	bool temp = Horde3D::setModelAnimParams((NodeHandle)lua_tonumber(Lua, 1), (int)lua_tonumber(Lua, 2), (float)lua_tonumber(Lua, 3), (float)lua_tonumber(Lua, 4));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::SetModelMorpher(lua_State *Lua)
{

	bool temp = Horde3D::setModelMorpher((NodeHandle)lua_tonumber(Lua, 1), lua_tostring(Lua, 2), (float)lua_tonumber(Lua, 3));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::AddMeshNode(lua_State *Lua)
{

	NodeHandle temp = Horde3D::addMeshNode((NodeHandle)lua_tonumber(Lua, 1), lua_tostring(Lua, 2), (ResHandle)lua_tonumber(Lua, 3),
										   (int)lua_tonumber(Lua, 4), (int)lua_tonumber(Lua, 5), (int)lua_tonumber(Lua, 6), (int)lua_tonumber(Lua, 7));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::AddJointNode(lua_State *Lua)
{

	NodeHandle temp = Horde3D::addJointNode((NodeHandle)lua_tonumber(Lua, 1), lua_tostring(Lua, 2), (int)lua_tonumber(Lua, 3));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::AddLightNode(lua_State *Lua)
{

	NodeHandle Node = 0;
	if (lua_tonumber(Lua, 1) == 0)
		Node = RootNode;
	else Node = (NodeHandle)lua_tonumber(Lua, 1);

	NodeHandle temp = Horde3D::addLightNode( Node, lua_tostring(Lua, 2), (ResHandle)lua_tonumber(Lua, 3), lua_tostring(Lua, 4), lua_tostring(Lua, 5) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::SetLightContexts(lua_State *Lua)
{

	bool temp = Horde3D::setLightContexts((NodeHandle)lua_tonumber(Lua, 1), lua_tostring(Lua, 2), lua_tostring(Lua, 3));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::SetupCameraView(lua_State *Lua)
{

	bool temp = Horde3D::setupCameraView((NodeHandle)lua_tonumber(Lua, 1), (float)lua_tonumber(Lua, 2), (float)lua_tonumber(Lua, 3), (float)lua_tonumber(Lua, 4), (float)lua_tonumber(Lua, 5) );

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::CalcCameraProjectionMatrix(lua_State *Lua)
{

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

int SGZHorde_Proxy::AddEmitterNode(lua_State *Lua)
{

	NodeHandle temp = Horde3D::addEmitterNode((NodeHandle)lua_tonumber(Lua, 1), lua_tostring(Lua, 2), (ResHandle)lua_tonumber(Lua, 3), (ResHandle)lua_tonumber(Lua, 4), (int)lua_tonumber(Lua, 5), (int)lua_tonumber(Lua, 6));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushnumber(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::AdvanceEmitterTime(lua_State *Lua)
{
	bool temp = Horde3D::advanceEmitterTime((NodeHandle)lua_tonumber(Lua, 1), (float)lua_tonumber(Lua, 2));

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	lua_pushboolean(Lua, temp);

	return 1;
}

int SGZHorde_Proxy::Init(lua_State *Lua)
{

	Horde3D::init();

	for (int cnt=1; cnt<=lua_gettop(Lua); cnt++)
		lua_pop(Lua, cnt);

	return 0;
}

const char SGZHorde_Proxy::className[] = "SGZHorde";
Lunar<SGZHorde_Proxy>::RegType SGZHorde_Proxy::methods[] =
{
	{"showText", &SGZHorde_Proxy::ShowText},
	{"getResourcePath", &SGZHorde_Proxy::GetResourcePath},
	{"setResourcePath", &SGZHorde_Proxy::SetResourcePath},
	{"loadResourcesFromDisk", &SGZHorde_Proxy::LoadResourcesFromDisk},
	{"pickNode", &SGZHorde_Proxy::PickNode},
	{"frameInfo", &SGZHorde_Proxy::FrameInfo},
	{"getStats", &SGZHorde_Proxy::GetStats},

	{"version", &SGZHorde_Proxy::Version},
	{"checkForExtension", &SGZHorde_Proxy::CheckForExtension},
	{"emptySceneGraph", &SGZHorde_Proxy::EmptySceneGraph},
	{"getMessage", &SGZHorde_Proxy::GetMessage},
	{"getOption", &SGZHorde_Proxy::GetOption},
	{"setOption", &SGZHorde_Proxy::SetOption},
	{"showOverlay", &SGZHorde_Proxy::ShowOverlay},
	{"clearOverlays", &SGZHorde_Proxy::ClearOverlays},
	{"render", &SGZHorde_Proxy::Render},
	{"resize", &SGZHorde_Proxy::Resize},

	{"getResourceType", &SGZHorde_Proxy::GetResourceType},
	{"getResourceName", &SGZHorde_Proxy::GetResourceName},
	{"findResource", &SGZHorde_Proxy::FindResource},
	{"addResource", &SGZHorde_Proxy::AddResource},
	{"cloneResource", &SGZHorde_Proxy::CloneResource},
	{"removeResource", &SGZHorde_Proxy::RemoveResource},
	{"loadResource", &SGZHorde_Proxy::LoadResource},
	{"unloadResource", &SGZHorde_Proxy::UnloadResource},
	{"getResourceParamInt", &SGZHorde_Proxy::GetResourceParamInt},
	{"getResourceParamFloat", &SGZHorde_Proxy::GetResourceParamFloat},
	{"getResourceData", &SGZHorde_Proxy::GetResourceData},
	{"updateResourceData", &SGZHorde_Proxy::UpdateResourceData},
	{"queryUnloadedResources", &SGZHorde_Proxy::QueryUnloadedResources},
	{"releaseUnusedResources", &SGZHorde_Proxy::ReleaseUnusedResources},

	{"create2DTexture", &SGZHorde_Proxy::Create2DTexture},
	{"setShaderPreambles", &SGZHorde_Proxy::SetShaderPreambles},
	{"setMaterialUniform", &SGZHorde_Proxy::SetMaterialUniform},
	{"setPipelineStageActivation", &SGZHorde_Proxy::SetPipelineStageActivation},
	{"getPipelineRenderTargetData", &SGZHorde_Proxy::GetPipelineRenderTargetData},

	{"getNodeType", &SGZHorde_Proxy::GetNodeType},
	{"getNodeName", &SGZHorde_Proxy::GetNodeName},
	{"setNodeName", &SGZHorde_Proxy::SetNodeName},
	{"getNodeParent", &SGZHorde_Proxy::GetNodeParent},
	{"setNodeParent", &SGZHorde_Proxy::SetNodeParent},
	{"getNodeChild", &SGZHorde_Proxy::GetNodeChild},
	{"getNodeAttachmentString", &SGZHorde_Proxy::GetNodeAttachmentString},
	{"addNodes", &SGZHorde_Proxy::AddNodes},
	{"removeNodes", &SGZHorde_Proxy::RemoveNodes},
	{"setNodeActivation", &SGZHorde_Proxy::SetNodeActivation},
	{"checkNodeTransformFlag", &SGZHorde_Proxy::CheckNodeTransformFlag},
	{"getNodeTransform", &SGZHorde_Proxy::GetNodeTransform},
	{"setNodeTransform", &SGZHorde_Proxy::SetNodeTransform},

	{"getNodeTransformMatrices", &SGZHorde_Proxy::GetNodeTransformMatrices},
	{"setNodeTransformMatrices", &SGZHorde_Proxy::SetNodeTransformMatrices},
	{"getNodeParamf", &SGZHorde_Proxy::GetNodeParamFloat},
	{"setNodeParami", &SGZHorde_Proxy::GetNodeParamInt},
	{"setNodeParamf", &SGZHorde_Proxy::SetNodeParamFloat},
	{"setNodeParami", &SGZHorde_Proxy::SetNodeParamInt},
	{"getNodeAABB", &SGZHorde_Proxy::GetNodeAABB},
	{"findNodes", &SGZHorde_Proxy::FindNodes},
	{"getNodeFindResult", &SGZHorde_Proxy::GetNodeFindResult},
	{"castRay", &SGZHorde_Proxy::CastRay},

	{"addGroupNode", &SGZHorde_Proxy::AddGroupNode},

	{"addModelNode", &SGZHorde_Proxy::AddModelNode},
	{"setupModelAnimStage", &SGZHorde_Proxy::SetupModelAnimStage},
	{"setModelAnimParams", &SGZHorde_Proxy::SetModelAnimParams},
	{"setModelMorpher", &SGZHorde_Proxy::SetModelMorpher},

	{"addMeshNode", &SGZHorde_Proxy::AddMeshNode},

	{"addJointNode", &SGZHorde_Proxy::AddJointNode},

	{"addLightNode", &SGZHorde_Proxy::AddLightNode},
	{"setLightContexts", &SGZHorde_Proxy::SetLightContexts},

	{"addCameraNode", &SGZHorde_Proxy::AddCameraNode},
	{"setupCameraView", &SGZHorde_Proxy::SetupCameraView},
	{"calcCameraProjectionMatrix", &SGZHorde_Proxy::CalcCameraProjectionMatrix},

	{"addEmitterNode", &SGZHorde_Proxy::AddEmitterNode},
	{"advanceEmitterTime", &SGZHorde_Proxy::AdvanceEmitterTime},

	{"init", &SGZHorde_Proxy::Init},

	{0,0}
};
#endif
