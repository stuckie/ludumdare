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

#include "GLEntity2D.h"

GLEntity2D::GLEntity2D()
{
	entityName = "Empty";
	CurrentAnim = "Default";
	position.x = position.y = position.z = 0.0f;
	looking.x = looking.y = looking.z = 0.0f;
	entitySpeed = entityAccel = maxEntityAccel = maxEntitySpeed = 0.0f;
	size.x = size.y = size.z = 1.0f;
	rotation.x = rotation.y = rotation.z = 0.0f;
	col.r = col.g = col.b = 1.0f;
	entityWidth = entityHeight = entityDepth = 1.0f;
};


GLEntity2D::GLEntity2D( std::string Name )
{
	entityName = Name;
};

bool GLEntity2D::Update ( void )
{
	/// Update our beloved entity
	SListIterator<SGZAnimGroup2D*> AnimListITR = AnimList.GetIterator();

	for( AnimListITR.Start(); AnimListITR.Valid(); AnimListITR.Forth() )
		if((AnimListITR.Item()->AnimName.compare(CurrentAnim))==0)
		{
			if(AnimListITR.Item()->FrameITR.Valid())
			{
				if(SGZ::Interpret.accessServer()->World()->accessTextureManager()->CheckExist(AnimListITR.Item()->FrameITR.Item()->TextureName))
				{
					glPushMatrix();
						glEnable(GL_BLEND);
							glDisable(GL_DEPTH_TEST);
								glDisable(GL_LIGHTING);
									glColor3f(1, 1, 1);
									glLoadIdentity();
									glTranslatef(position.x, position.y, position.z);
									glScalef(size.x, size.y, size.z);
									glRotatef(rotation.x, 1.0, 0.0, 0.0);
									glRotatef(rotation.y, 0.0, 1.0, 0.0);
									glRotatef(rotation.z, 0.0, 0.0, 1.0);
									glBlendFunc( GL_DST_COLOR, GL_ZERO );
									SGZ::Interpret.accessServer()->World()->accessTextureManager()->GetTextureMask(AnimListITR.Item()->FrameITR.Item()->TextureName);
									glBegin ( GL_QUADS );
										glNormal3f(0.0f, 0.0f, 1.0f);
										glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);	// Point 1
										glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  0.0f);	// Point 2
										glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  0.0f);	// Point 3
										glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  0.0f);	// Point 4
									glEnd();
									glColor3f(col.r, col.g, col.b);
									glBlendFunc( GL_ONE, GL_ONE );
									SGZ::Interpret.accessServer()->World()->accessTextureManager()->GetTexture(AnimListITR.Item()->FrameITR.Item()->TextureName);
									glBegin ( GL_QUADS );
										glNormal3f(0.0f, 0.0f, 1.0f);
										glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);	// Point 1
										glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  0.0f);	// Point 2
										glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  0.0f);	// Point 3
										glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  0.0f);	// Point 4
									glEnd();
								glEnable(GL_LIGHTING);
							glEnable(GL_DEPTH_TEST);
						glDisable(GL_BLEND);
					glPopMatrix();
				}

				if(AnimListITR.Item()->AnimTimer.currenttime() >= AnimListITR.Item()->FrameITR.Item()->delay)
				{
					AnimListITR.Item()->FrameITR.Forth();
					AnimListITR.Item()->CurAnim++;
					AnimListITR.Item()->AnimTimer.reset();
				}

				if (AnimListITR.Item()->FrameList.Size() == AnimListITR.Item()->CurAnim)
				{
					AnimListITR.Item()->CurAnim = 0;
					AnimListITR.Item()->FrameITR.Start();
				}
			}
		}
	position.x -= looking.x*entitySpeed;
	position.y -= looking.y*entitySpeed;
	position.z -= looking.z*entitySpeed;

	return true;
}

/*bool GLEntity2D::Update( void )
{
	/// Update our beloved entity
	SListIterator<AnimGroup*> AnimListITR = AnimList.GetIterator();

	for( AnimListITR.Start(); AnimListITR.Valid(); AnimListITR.Forth() )
		if((AnimListITR.Item()->AnimName.compare(CurrentAnim))==0)
		{
			SDL_Rect offset;
			if(AnimListITR.Item()->TEXListITR.Valid())
			{
					glPushMatrix();
						glEnable(GL_BLEND);
							glDisable(GL_DEPTH_TEST);
								glDisable(GL_LIGHTING);
									glColor3f(1, 1, 1);
									glLoadIdentity();
									glTranslatef(position.x, position.y, position.z);
									glScalef(size.x, size.y, size.z);
									glRotatef(rotation.x, 1.0, 0.0, 0.0);
									glRotatef(rotation.y, 0.0, 1.0, 0.0);
									glRotatef(rotation.z, 0.0, 0.0, 1.0);
									glBlendFunc( GL_DST_COLOR, GL_ZERO );
									AnimListITR.Item()->TEXListITR.Item()->GetTextureMask();
									glBegin ( GL_QUADS );
										glNormal3f(0.0f, 0.0f, 1.0f);
										glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);	// Point 1
										glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  0.0f);	// Point 2
										glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  0.0f);	// Point 3
										glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  0.0f);	// Point 4
									glEnd();
									glColor3f(col.r, col.g, col.b);
									glBlendFunc( GL_ONE, GL_ONE );
									AnimListITR.Item()->TEXListITR.Item()->GetTexture();
									glBegin ( GL_QUADS );
										glNormal3f(0.0f, 0.0f, 1.0f);
										glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);	// Point 1
										glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  0.0f);	// Point 2
										glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  0.0f);	// Point 3
										glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  0.0f);	// Point 4
									glEnd();
								glEnable(GL_LIGHTING);
							glEnable(GL_DEPTH_TEST);
						glDisable(GL_BLEND);
					glPopMatrix();
			}
			AnimListITR.Item()->TEXListITR.Forth();
			AnimListITR.Item()->CurAnim++;
			if (AnimListITR.Item()->TEXList.Size() == AnimListITR.Item()->CurAnim)
			{
				AnimListITR.Item()->CurAnim = 0;
				AnimListITR.Item()->TEXListITR.Start();
			}
		}

	position.x -= looking.x*entitySpeed;
	position.y -= looking.y*entitySpeed;
	position.z -= looking.z*entitySpeed;

	return true;
}*/

SGZ::SCALER GLEntity2D::GetWidth ( void )
{
	return entityWidth;
}

SGZ::SCALER GLEntity2D::GetHeight( void )
{
	return entityHeight;
}

SGZ::SCALER GLEntity2D::GetDepth( void )
{
	return entityDepth;
}

bool GLEntity2D::Cleanup ( void )
{
	/** Clean up our entity mess! */
	return true;
}

bool GLEntity2D::MoveTo ( SGZ::VECTOR3 vector )
{
	/** Move to direct co-ordinates */
	position = vector;
	return true;
}

bool GLEntity2D::LookTo ( SGZ::VECTOR3 vector )
{
	/** Direction to look at ( move towards ) */
	looking.x = position.x - vector.x;
	looking.y = position.y - vector.y;
	looking.z = position.z - vector.z;
	return true;
}

bool GLEntity2D::MoveDelta ( SGZ::VECTOR3 vector )
{
	position.x += vector.x;
	position.y += vector.y;
	position.z += vector.z;
	return true;
}

bool GLEntity2D::MoveDeltaX ( SGZ::SCALER amount )
{
	position.x += amount;
	return true;
}

bool GLEntity2D::MoveDeltaY ( SGZ::SCALER amount )
{
	position.y += amount;
	return true;
}

bool GLEntity2D::MoveDeltaZ ( SGZ::SCALER amount )
{
	position.z += amount;
	return true;
}

bool GLEntity2D::Scale ( SGZ::SCALER value )
{
	size.x=value;
	size.y=value;
	size.z=value;

	return true;
}

bool GLEntity2D::ScaleX ( SGZ::SCALER value )
{
	size.x = value;
	return true;
}

bool GLEntity2D::ScaleY ( SGZ::SCALER value )
{
	size.y = value;
	return true;
}

bool GLEntity2D::ScaleZ ( SGZ::SCALER value )
{
	size.z=value;
	return true;
}

bool GLEntity2D::ScaleXYZ ( SGZ::VECTOR3 vector )
{
	size.x = vector.x;
	size.y = vector.y;
	size.z = vector.z;

	return true;
}

bool GLEntity2D::RotateX ( SGZ::SCALER value )
{
	rotation.x=value;
	return true;
}

bool GLEntity2D::RotateY ( SGZ::SCALER value )
{
	rotation.y=value;
	return true;
}

bool GLEntity2D::RotateZ ( SGZ::SCALER value )
{
	rotation.z=value;
	return true;
}

bool GLEntity2D::Rotate ( SGZ::VECTOR3 vector )
{
	rotation = vector;
	return true;
}

bool GLEntity2D::MaxAccel ( SGZ::SCALER value )
{
	maxEntityAccel = value;
	return true;
}

bool GLEntity2D::SetWidth ( SGZ::SCALER value )
{
	entityWidth = value;
	return true;
}

bool GLEntity2D::SetHeight ( SGZ::SCALER value )
{
	entityHeight = value;
	return true;
}

bool GLEntity2D::SetDepth ( SGZ::SCALER value )
{
	entityDepth = value;
	return true;
}

bool GLEntity2D::SetAccel ( SGZ::SCALER value )
{
	entityAccel = value;
	return true;
}

bool GLEntity2D::MaxSpeed ( SGZ::SCALER value )
{
	maxEntitySpeed = value;
	return true;
}

bool GLEntity2D::SetSpeed ( SGZ::SCALER value )
{
	entitySpeed = value;
	return true;
}

bool GLEntity2D::Stop ( void )
{
	/** Stop moving/rotating/scaling immediately */
	entitySpeed = 0;
	entityAccel = 0;

	return true;
}

bool GLEntity2D::SetCollisionGeom ( int type )
{
	/** Set the collision type */

	return true;
}

bool GLEntity2D::SetAnimation( std::string Name )
{
	CurrentAnim = Name;

	return true;
}

bool GLEntity2D::CreateAnimation( std::string Name )
{
	SGZAnimGroup2D *Animation = new SGZAnimGroup2D;
	Animation->AnimTimer.start();
	Animation->AnimName = Name;
	Animation->AnimNum = 0;
	Animation->CurAnim = 0;
	AnimList.Append(Animation);

	return true;
}

bool GLEntity2D::DeleteAnimation( std::string Name )
{
	SListIterator<SGZAnimGroup2D*> AnimListITR = AnimList.GetIterator();

	for( AnimListITR.Start(); AnimListITR.Valid(); AnimListITR.Forth() )
		if((AnimListITR.Item()->AnimName.compare(Name))==0)
		{
			AnimListITR.Item()->FrameITR.Start();
			while (AnimListITR.Item()->FrameITR.Valid())
			{
				AnimListITR.Item()->FrameList.Remove(AnimListITR.Item()->FrameITR);
				AnimListITR.Item()->FrameITR.Forth();
			}

			AnimList.Remove(AnimListITR);
			return true;
		}

	Logger.log( SGZLOG::Warning, "Animation \"" + Name + "\" does not exist!\n");
	return false;
}

bool GLEntity2D::LoadFrame ( std::string Name, std::string TexName, std::string MaskName, int FrameDelay, int x, int y, SGZ::RGBCOLOUR ColourKey )
{
	/// Load up a Texture into an Animation
	SListIterator<SGZAnimGroup2D*> AnimListITR = AnimList.GetIterator();

	for( AnimListITR.Start(); AnimListITR.Valid(); AnimListITR.Forth() )
		if((AnimListITR.Item()->AnimName.compare(Name))==0)
		{
			SGZAnimFrame2D *Frame = new SGZAnimFrame2D;
			Frame->TextureName = TexName;
			Frame->MaskName = MaskName;
			Frame->delay = FrameDelay;
			Frame->u = x;
			Frame->v = y;
			Frame->colkey = ColourKey;
			AnimListITR.Item()->FrameList.Append(Frame);
			AnimListITR.Item()->AnimNum++;
			AnimListITR.Item()->FrameITR = AnimListITR.Item()->FrameList.GetIterator();

			if(!SGZ::Interpret.accessServer()->World()->accessTextureManager()->CheckExist(TexName))
				Logger.log( SGZLOG::Warning, "Texture \"%s\" has not been loaded yet!\n[!!] Make sure it is before calling frame \"%s\"!\n", TexName.c_str(), Name.c_str());
			return true;
		}

	Logger.log( SGZLOG::Warning, "Animation \"" + Name + "\" does not exist!\n");
	return false;
}

/*bool GLEntity2D::CreateAnimation( std::string Name )
{
	AnimGroup *Animation = new AnimGroup;
	Animation->AnimName = Name;
	Animation->AnimNum = 0;
	Animation->CurAnim = 0;
	AnimList.Append(Animation);

	return true;
}

bool GLEntity2D::DeleteAnimation( std::string Name )
{
	SListIterator<AnimGroup*> AnimListITR = AnimList.GetIterator();

	for( AnimListITR.Start(); AnimListITR.Valid(); AnimListITR.Forth() )
		if((AnimListITR.Item()->AnimName.compare(Name))==0)
		{
			AnimList.Remove(AnimListITR);
			return true;
		}

	Logger.log( SGZLOG::Warning, "Animation \"" + Name + "\" does not exist!\n");
	return false;
}

bool GLEntity2D::LoadFrame ( std::string Name, std::string TexName, std::string MaskName, int FrameDelay, int x, int y, SGZ::RGBCOLOUR ColourKey )
{
	/// Load up a Texture into an Animation
	SListIterator<AnimGroup*> AnimListITR = AnimList.GetIterator();

	for( AnimListITR.Start(); AnimListITR.Valid(); AnimListITR.Forth() )
		if((AnimListITR.Item()->AnimName.compare(Name))==0)
		{
			OTexture *Texture = new OTexture;
			Texture->CreateTexture();
			Texture->LoadTexture(TexName);
			Texture->LoadTextureMask(MaskName);
			AnimListITR.Item()->TEXList.Append(Texture);
			AnimListITR.Item()->AnimNum++;
			AnimListITR.Item()->TEXListITR = AnimListITR.Item()->TEXList.GetIterator();
			return true;
		}

	Logger.log( SGZLOG::Warning, "Animation \"" + Name + "\" does not exist!\n");
	return false;
}
*/
bool GLEntity2D::SetName( std::string Name )
{
	entityName = Name;
	return true;
}

std::string GLEntity2D::GetName ( void )
{
	return entityName;
}

std::string GLEntity2D::GetAnimation( void )
{
	return CurrentAnim;
}

SGZ::SCALER GLEntity2D::GetAccel ( void )
{
	return entityAccel;
}

SGZ::SCALER GLEntity2D::GetLookZ ( void )
{
	return looking.z;
}

SGZ::SCALER GLEntity2D::GetLookY ( void )
{
	return looking.y;
}

SGZ::SCALER GLEntity2D::GetLookX ( void )
{
	return looking.x;
}

SGZ::SCALER GLEntity2D::GetZ ( void )
{
	return position.z;
}
SGZ::SCALER GLEntity2D::GetY ( void )
{
	return position.y;
}
SGZ::SCALER GLEntity2D::GetX ( void )
{
	return position.x;
}

SGZ::SCALER GLEntity2D::GetSpeed( void )
{
	return entitySpeed;
}

bool GLEntity2D::Colour ( SGZ::RGBCOLOUR input )
{
	col = input;
	return true;
}

bool GLEntity2D::NewVar( std::string Name )
{
	SGZVarGroup *Variable = new SGZVarGroup;
	Variable->Name = Name;
	Variable->Variable = "none";
	VarList.Append(Variable);

	return true;
}

bool GLEntity2D::DeleteVar( std::string Name )
{
	SListIterator<SGZVarGroup*> VarITR = VarList.GetIterator();

	for( VarITR.Start(); VarITR.Valid(); VarITR.Forth() )
		if((VarITR.Item()->Name.compare(Name))==0)
		{
			VarList.Remove(VarITR);
			return true;
		}

	Logger.log( SGZLOG::Warning, "Variable \"" + Name + "\" does not exist!\n");
	return false;
}

bool GLEntity2D::ChangeVar ( std::string Name, std::string Value )
{
	/** Load up a Texture into an Animation*/
	SListIterator<SGZVarGroup*> VarITR = VarList.GetIterator();

	for( VarITR.Start(); VarITR.Valid(); VarITR.Forth() )
		if((VarITR.Item()->Name.compare(Name))==0)
		{
			VarITR.Item()->Variable = Value;
			return true;
		}

	Logger.log( SGZLOG::Warning, "Variable \"" + Name + "\" does not exist!\n");
	return false;
}

std::string GLEntity2D::CheckVar( std::string Name )
{
	SListIterator<SGZVarGroup*> VarITR = VarList.GetIterator();

	for( VarITR.Start(); VarITR.Valid(); VarITR.Forth() )
		if((VarITR.Item()->Name.compare(Name))==0)
			return VarITR.Item()->Variable;

	return "none";
}
