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

#ifndef _SGZHORDE_H_
#define _SGZHORDE_H_


#include "../../../arch.h"

#if defined(REND_HORDE) || defined(REND_SDLHORDE)

#ifdef pedanticGCC
extern "C" {
#endif
	#include "../lualib.h"
#ifdef pedanticGCC
}
#endif

#include "../lunar.h"
#include "../../../common/debug/CDebug.h"
#include "../../../system/horde/renderer/HordeRender.h"
#include "../../../common/data/CSLinkedlist.h"

class SGZHorde_Proxy
{
	public:
		static const char className[];
		static Lunar<SGZHorde_Proxy>::RegType methods[];

		/**
			Horde3DUtils
						*/
		int GetResourcePath(lua_State *Lua);
		int SetResourcePath(lua_State *Lua);
		int LoadResourcesFromDisk(lua_State *Lua);
		int PickNode(lua_State *Lua);
		int ShowText(lua_State *Lua);
		int FrameInfo(lua_State *Lua);
		int GetStats(lua_State *Lua);

		/**
			Horde3D
					*/

		int SetOption(lua_State *Lua);
		int Version(lua_State *Lua);
		int CheckForExtension(lua_State *Lua);
		int EmptySceneGraph(lua_State *Lua);
		int GetMessage(lua_State *Lua);
		int GetOption(lua_State *Lua);
		int ShowOverlay(lua_State *Lua);
		int ClearOverlays(lua_State *Lua);
		int Render(lua_State *Lua);
		int Resize(lua_State *Lua);

		int GetResourceType(lua_State *Lua);
		int GetResourceName(lua_State *Lua);
		int AddResource(lua_State *Lua);
		int FindResource(lua_State *Lua);
		int CloneResource(lua_State *Lua);
		int RemoveResource(lua_State *Lua);
		int LoadResource(lua_State *Lua);
		int UnloadResource(lua_State *Lua);
		int GetResourceParamInt(lua_State *Lua);
		int GetResourceParamFloat(lua_State *Lua);
		int GetResourceData(lua_State *Lua);
		int UpdateResourceData(lua_State *Lua);
		int QueryUnloadedResources(lua_State *Lua);
		int ReleaseUnusedResources(lua_State *Lua);

		int Create2DTexture(lua_State *Lua);
		int SetShaderPreambles(lua_State *Lua);
		int SetMaterialUniform(lua_State *Lua);
		int SetPipelineStageActivation(lua_State *Lua);
		int GetPipelineRenderTargetData(lua_State *Lua);

		int GetNodeType(lua_State *Lua);
		int GetNodeName(lua_State *Lua);
		int SetNodeName(lua_State *Lua);
		int GetNodeParent(lua_State *Lua);
		int SetNodeParent(lua_State *Lua);
		int GetNodeChild(lua_State *Lua);
		int GetNodeAttachmentString(lua_State *Lua);
		int AddNodes(lua_State *Lua);
		int RemoveNodes(lua_State *Lua);
		int SetNodeActivation(lua_State *Lua);
		int CheckNodeTransformFlag(lua_State *Lua);
		int GetNodeTransform(lua_State *Lua);
		int SetNodeTransform(lua_State *Lua);

		int SetNodeTransformODEDynamic(lua_State *Lua);
		int SetNodeTransformODEScripted(lua_State *Lua);
		int SetNodeTransformODEDynamicWithScale(lua_State *Lua);
		int SetNodeTransformODEScriptedWithScale(lua_State *Lua);
		int SetNodeTransformODEDynamicNoScale(lua_State *Lua);
		int SetNodeTransformODEScriptedNoScale(lua_State *Lua);
		int SetNodeTransformODEScriptedNoScaleUsingOriginalPos(lua_State *Lua);
		int SetNodeTransformODEScriptedNoScaleNoRot(lua_State *Lua);

		int SetPlayerTransform(lua_State *Lua);
		int GetNodeTransformMatrices(lua_State *Lua);
		int SetNodeTransformMatrices(lua_State *Lua);
		int GetNodeParamFloat(lua_State *Lua);
		int GetNodeParamInt(lua_State *Lua);
		int SetNodeParamInt(lua_State *Lua);
		int SetNodeParamFloat(lua_State *Lua);
		int GetNodeAABB(lua_State *Lua);
		int FindNodes(lua_State *Lua);
		int GetNodeFindResult(lua_State *Lua);
		int CastRay(lua_State *Lua);

		int AddGroupNode(lua_State *Lua);

		int AddModelNode(lua_State *Lua);
		int SetupModelAnimStage(lua_State *Lua);
		int SetModelAnimParams(lua_State *Lua);
		int SetModelMorpher(lua_State *Lua);

		int AddMeshNode(lua_State *Lua);

		int AddJointNode(lua_State *Lua);

		int AddLightNode(lua_State *Lua);
		int SetLightContexts(lua_State *Lua);

		int AddCameraNode(lua_State *Lua);
		int SetupCameraView(lua_State *Lua);
		int CalcCameraProjectionMatrix(lua_State *Lua);

		int AddEmitterNode(lua_State *Lua);
		int AdvanceEmitterTime(lua_State *Lua);

		int Init(lua_State *Lua);

		int AddParticleEffect(lua_State *Lua);
		int AddParticleBox(lua_State *Lua);

		SGZHorde_Proxy(lua_State *L)
		{
			for (int cnt=1; cnt<=lua_gettop(L); cnt++)
				lua_pop(L, cnt);
		}
		~SGZHorde_Proxy() {}

	private:

};

#endif
#endif
