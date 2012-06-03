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

#include "SDLEntity2D.h"
#include "../../../common/engine/CInterpret.h"
#include "../../../server/OServer.h"
#include "../../../server/gameServer/GameServer.h"
#include "../../../server/managers/textureManager/MTexture.h"

bool SDLEntity2D::Update ( float deltaTime )
{
	mDeltaTime = deltaTime;
	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;
	position.z += velocity.z * deltaTime;

	/// Update our beloved entity
	SListIterator<SGZAnimGroup2D*> AnimListITR = AnimList.getIterator();

	offset.x = (Uint16)position.x;
	offset.y = (Uint16)position.y;
	offset.w = (Uint16)entityWidth;
	offset.h = (Uint16)entityHeight;

	//CurrentFrame = SDL_GetVideoSurface();
	
	for( AnimListITR.start(); AnimListITR.valid(); AnimListITR.forth() )
		if((AnimListITR.item()->AnimName.compare(CurrentAnim))==0)
		{
			if(AnimListITR.item()->AnimTimer.currenttime() >= AnimListITR.item()->FrameITR.item()->delay)
			{
				AnimListITR.item()->FrameITR.forth();
				AnimListITR.item()->CurAnim++;
				AnimListITR.item()->AnimTimer.reset();
			}

			if (AnimListITR.item()->FrameList.size() == AnimListITR.item()->CurAnim)
			{
				AnimListITR.item()->CurAnim = 0;
				AnimListITR.item()->FrameITR.start();
			}
			
			if(AnimListITR.item()->FrameITR.valid())
			{
				frame.x = (Uint16)AnimListITR.item()->FrameITR.item()->u;
				frame.y = (Uint16)AnimListITR.item()->FrameITR.item()->v;
				frame.w = (Uint16)entityWidth;
				frame.h = (Uint16)entityHeight;

				CurrentFrame = static_cast<SDL_Surface*>(manTextures->getTexture(AnimListITR.item()->FrameITR.item()->TextureName));
				SDL_SetColorKey(CurrentFrame, SDL_SRCCOLORKEY, SDL_MapRGB(	CurrentFrame->format,
																			(Uint32)AnimListITR.item()->FrameITR.item()->colkey.r,
																			(Uint32)AnimListITR.item()->FrameITR.item()->colkey.g,
																			(Uint32)AnimListITR.item()->FrameITR.item()->colkey.b));

				offset.w = (Uint16)entityWidth;
				offset.h = (Uint16)entityHeight;
				offset.x = (Sint16)position.x;
				offset.y = (Sint16)position.y;
				
				Uint32 old32Colour = SDL_MapRGB(	CurrentFrame->format,
													oldColour.r,
													oldColour.g,
													oldColour.b);
				
				Uint32 new32Colour = SDL_MapRGB(	CurrentFrame->format,
													newColour.r,
													newColour.g,
													newColour.b);
													
				//SDL_LockSurface(CurrentFrame);
				
				SDL_BlitSurface(CurrentFrame, &frame, SDL_GetVideoSurface(), &offset );
													
				if (SDL_GetVideoSurface()->format->BitsPerPixel == 16) {
					Uint16 *pixels = (Uint16 *)SDL_GetVideoSurface()->pixels;
					for (int index_y = offset.y; index_y < offset.y + offset.h; ++index_y){
						for (int index_x = offset.x; index_x < offset.x + offset.w; ++index_x){
							Uint16 colour = pixels[ ( index_y * SDL_GetVideoSurface()->w ) + index_x ];
 
							if ( colour == old32Colour )
								pixels[ ( index_y * SDL_GetVideoSurface()->w ) + index_x ] = new32Colour;
							else
								pixels[ ( index_y * SDL_GetVideoSurface()->w ) + index_x ] = colour;
						}
					}
				}
				else {
					Uint32 *pixels = (Uint32 *)CurrentFrame->pixels;
					for (int index_y = 0; index_y < CurrentFrame->h; ++index_y){
						for (int index_x = 0; index_x < CurrentFrame->w; ++index_x){
							Uint32 colour = pixels[ ( index_y * CurrentFrame->w ) + index_x ];
 
							if ( colour == old32Colour )
								pixels[ ( index_y * CurrentFrame->w ) + index_x ] = new32Colour;
							else
								pixels[ ( index_y * CurrentFrame->w ) + index_x ] = colour;
						}
					}
				}
				
				//SDL_UnlockSurface(CurrentFrame);
			}
			
			return true;
		}

	return true;
}

SGZ::SCALER SDLEntity2D::GetWidth ( void )
{
	return entityWidth;
}

SGZ::SCALER SDLEntity2D::GetHeight( void )
{
	return entityHeight;
}

SGZ::SCALER SDLEntity2D::GetDepth( void )
{
	return entityDepth;
}

bool SDLEntity2D::SetWidth( SGZ::SCALER width )
{
	entityWidth = width;
	return true;
}

bool SDLEntity2D::SetHeight( SGZ::SCALER height )
{
	entityHeight = height;
	return true;
}

bool SDLEntity2D::SetDepth( SGZ::SCALER depth )
{
	entityDepth = depth;
	return true;
}

bool SDLEntity2D::Cleanup ( void )
{
	/** Clean up our entity mess! */
	return true;
}

bool SDLEntity2D::MoveTo ( SGZ::VECTOR3 vector )
{
	/** Move to direct co-ordinates */
	position = vector;
	return true;
}

bool SDLEntity2D::LookTo ( SGZ::VECTOR3 vector )
{
	/** Direction to look at ( move towards ) */
	looking = vector;
	return true;
}

bool SDLEntity2D::MoveDelta ( SGZ::VECTOR3 amount )
{
	position.x += amount.x * mDeltaTime;
	position.y += amount.y * mDeltaTime;
	position.z += amount.z * mDeltaTime;
	return true;
}

bool SDLEntity2D::MoveDeltaX ( SGZ::SCALER amount )
{
	position.x += amount;
	return true;
}

bool SDLEntity2D::MoveDeltaY ( SGZ::SCALER amount )
{
	position.y += amount;
	return true;
}

bool SDLEntity2D::MoveDeltaZ ( SGZ::SCALER amount )
{
	position.z += amount;
	return true;
}

bool SDLEntity2D::Scale ( SGZ::SCALER value )
{
	zoomX=value;
	zoomY=value;

	return true;
}

bool SDLEntity2D::ScaleX ( SGZ::SCALER value )
{
	zoomX = value;
	return true;
}

bool SDLEntity2D::ScaleY ( SGZ::SCALER value )
{
	zoomY = value;
	return true;
}

bool SDLEntity2D::ScaleZ ( SGZ::SCALER )
{
	return true;
}

bool SDLEntity2D::RotateX ( SGZ::SCALER value )
{
	angle=value;
	return true;
}

bool SDLEntity2D::ScaleXYZ ( SGZ::VECTOR3  )
{
	return true;
}

bool SDLEntity2D::Rotate ( SGZ::VECTOR3 )
{
	return true;
}

bool SDLEntity2D::RotateY ( SGZ::SCALER value )
{
	angle=value;
	return true;
}

bool SDLEntity2D::RotateZ ( SGZ::SCALER value )
{
	angle=value;
	return true;
}

bool SDLEntity2D::MaxAccel ( SGZ::SCALER value )
{
	maxEntityAccel = value;
	return true;
}

bool SDLEntity2D::SetAccel ( SGZ::SCALER value )
{
	entityAccel = value;
	return true;
}

bool SDLEntity2D::Stop ( void )
{
	/** Stop moving/rotating/scaling immediately */
	entitySpeed = 0;
	entityAccel = 0;

	return true;
}

bool SDLEntity2D::SetCollisionGeom ( int )
{
	/** Set the collision type */

	return true;
}

bool SDLEntity2D::SetAnimation( std::string Name )
{
	CurrentAnim = Name;

	return true;
}

bool SDLEntity2D::CreateAnimation( std::string Name )
{
	SGZAnimGroup2D *Animation = new SGZAnimGroup2D;
	Animation->AnimTimer.start();
	Animation->AnimName = Name;
	Animation->AnimNum = 0;
	Animation->CurAnim = 0;
	AnimList.append(Animation);

	return true;
}

bool SDLEntity2D::DeleteAnimation( std::string Name )
{
	SListIterator<SGZAnimGroup2D*> AnimListITR = AnimList.getIterator();

	for( AnimListITR.start(); AnimListITR.valid(); AnimListITR.forth() )
		if((AnimListITR.item()->AnimName.compare(Name))==0)
		{
			AnimListITR.item()->FrameITR.start();
			while (AnimListITR.item()->FrameITR.valid())
			{
				AnimListITR.item()->FrameList.remove(AnimListITR.item()->FrameITR);
				AnimListITR.item()->FrameITR.forth();
			}

			AnimList.remove(AnimListITR);
			return true;
		}

	SGZ::Logger.log( SGZLOG::Warning, "Animation \"" + Name + "\" does not exist!\n");
	return false;
}

bool SDLEntity2D::LoadFrame ( std::string Name, std::string TexName, std::string MaskName, int FrameDelay, int x, int y, SGZ::RGBCOLOUR ColourKey )
{
	/// Load up a Texture into an Animation
	SListIterator<SGZAnimGroup2D*> AnimListITR = AnimList.getIterator();

	for( AnimListITR.start(); AnimListITR.valid(); AnimListITR.forth() )
		if((AnimListITR.item()->AnimName.compare(Name))==0)
		{
			SGZAnimFrame2D *Frame = new SGZAnimFrame2D;
			Frame->TextureName = TexName;
			Frame->MaskName = MaskName;
			Frame->delay = FrameDelay;
			Frame->u = x;
			Frame->v = y;
			Frame->colkey = ColourKey;
			AnimListITR.item()->FrameList.append(Frame);
			AnimListITR.item()->AnimNum++;
			AnimListITR.item()->FrameITR = AnimListITR.item()->FrameList.getIterator();

			if(!manTextures->checkExist(TexName))
				SGZ::Logger.log( SGZLOG::Warning, "Texture " + TexName + " has not been loaded yet.. make sure it is before calling this frame!");
			return true;
		}

	SGZ::Logger.log( SGZLOG::Warning, "Animation \"" + Name + "\" does not exist!\n");
	return false;
}

bool SDLEntity2D::SetName( std::string Name )
{
	entityName = Name;
	return true;
}

SGZ::SCALER SDLEntity2D::GetX(void)
{
	return position.x;
}

SGZ::SCALER SDLEntity2D::GetY(void)
{
	return position.y;
}

SGZ::SCALER SDLEntity2D::GetZ(void)
{
	return position.z;
}

SGZ::SCALER SDLEntity2D::GetLookX(void)
{
	return looking.x;
}

SGZ::SCALER SDLEntity2D::GetLookY(void)
{
	return looking.y;
}

SGZ::SCALER SDLEntity2D::GetLookZ(void)
{
	return looking.z;
}

SGZ::SCALER SDLEntity2D::GetAccel(void)
{
	return entityAccel;
}

SGZ::SCALER SDLEntity2D::GetSpeed(void)
{
	return entitySpeed;
}

std::string SDLEntity2D::GetAnimation(void)
{
	return CurrentAnim;
}

std::string SDLEntity2D::GetName(void)
{
	return entityName;
}

bool SDLEntity2D::Colour ( SGZ::RGBCOLOUR input )
{
	col = input;
	return true;
}

bool SDLEntity2D::ChangeColour( SGZ::RGBCOLOUR pOldColour, SGZ::RGBCOLOUR pNewColour )
{
	oldColour = pOldColour;
	newColour = pNewColour;
	return true;
}

bool SDLEntity2D::SetSpeed ( SGZ::SCALER value )
{
	entitySpeed = value;
	return true;
}

bool SDLEntity2D::MaxSpeed ( SGZ::SCALER value )
{
	maxEntitySpeed = value;
	return true;
}

bool SDLEntity2D::NewVar( std::string Name )
{
	SGZVarGroup *Variable = new SGZVarGroup;
	Variable->Name = Name;
	Variable->Variable = "none";
	VarList.append(Variable);

	return true;
}

bool SDLEntity2D::DeleteVar( std::string Name )
{
	SListIterator<SGZVarGroup*> VarITR = VarList.getIterator();

	for( VarITR.start(); VarITR.valid(); VarITR.forth() )
		if((VarITR.item()->Name.compare(Name))==0)
		{
			VarList.remove(VarITR);
			return true;
		}

	SGZ::Logger.log( SGZLOG::Warning, "Variable \"" + Name + "\" does not exist!\n");
	return false;
}

bool SDLEntity2D::ChangeVar ( std::string Name, std::string Value )
{
	/** Load up a Texture into an Animation*/
	SListIterator<SGZVarGroup*> VarITR = VarList.getIterator();

	for( VarITR.start(); VarITR.valid(); VarITR.forth() )
		if((VarITR.item()->Name.compare(Name))==0)
		{
			VarITR.item()->Variable = Value;
			return true;
		}

	SGZ::Logger.log( SGZLOG::Warning, "Variable \"" + Name + "\" does not exist!\n");
	return false;
}

std::string SDLEntity2D::CheckVar( std::string Name )
{
	SListIterator<SGZVarGroup*> VarITR = VarList.getIterator();

	for( VarITR.start(); VarITR.valid(); VarITR.forth() )
		if((VarITR.item()->Name.compare(Name))==0)
			return VarITR.item()->Variable;

	return "none";
}

