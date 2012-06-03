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

#include "MTexture.h"
#include "../../../common/debug/CDebug.h"
#include "../../../client/renderer/texture/OTexture.h"

MTexture::MTexture()
:   mTextureList()
{
	/** Constructor */
	SListIterator<TextureObj*> TextureITR = mTextureList.getIterator();
	SGZ::Logger.log( SGZLOG::Debug, "SGZTextureManager Started\n");
}

MTexture::~MTexture()
{
	/** Destructor */
	SListIterator<TextureObj*> TextureITR = mTextureList.getIterator();

	TextureITR.start();
	while (TextureITR.valid())
	{
		mTextureList.remove(TextureITR);
		TextureITR.forth();
	}
}

bool MTexture::addTexture( const std::string &TexName, const std::string &Filename )
{
	TextureObj* Texture = new TextureObj;
	Texture->mName = TexName;
	Texture->mData->createTexture();
	Texture->mData->loadTexture(Filename);
	mTextureList.append(Texture);

	return true;
}
bool MTexture::addTexMask( const std::string &Name, const std::string &Maskname )
{
	SListIterator<TextureObj*> TextureITR = mTextureList.getIterator();
	for( TextureITR.start(); TextureITR.valid(); TextureITR.forth() )
		if(TextureITR.item()->mName.compare(Name)==0)
		{
			TextureITR.item()->mData->loadTextureMask(Maskname);
			return true;
		}

	SGZ::Logger.log( SGZLOG::Warning, "Texture " + Name + " does not exist!\n");
	return false;
}
bool MTexture::delTexture( const std::string &Name )
{
	SListIterator<TextureObj*> TextureITR = mTextureList.getIterator();
	for( TextureITR.start(); TextureITR.valid(); TextureITR.forth() )
		if(TextureITR.item()->mName.compare(Name)==0)
		{
			mTextureList.remove(TextureITR);
			return true;
		}

	SGZ::Logger.log( SGZLOG::Warning, "Texture " + Name + " does not exist!\n");
	return false;
}

TextureObj* MTexture::getObj ( const std::string &Name )
{
	SListIterator<TextureObj*> TextureITR = mTextureList.getIterator();
	for( TextureITR.start(); TextureITR.valid(); TextureITR.forth() )
		if(TextureITR.item()->mName.compare(Name)==0)
		{
			return TextureITR.item();
		}

	SGZ::Logger.log( SGZLOG::Warning, "Texture " + Name + " does not exist!\n");
	return NULL;
}

void* MTexture::getTexture( const std::string &Name )
{
	SListIterator<TextureObj*> TextureITR = mTextureList.getIterator();
	for( TextureITR.start(); TextureITR.valid(); TextureITR.forth() )
		if(TextureITR.item()->mName.compare(Name)==0)
		{
			return TextureITR.item()->mData->getTexture();
		}

	SGZ::Logger.log( SGZLOG::Warning, "Texture " + Name + " does not exist!\n");
	return NULL;
}

void* MTexture::getTextureMask( const std::string &Name )
{
	SListIterator<TextureObj*> TextureITR = mTextureList.getIterator();
	for( TextureITR.start(); TextureITR.valid(); TextureITR.forth() )
		if(TextureITR.item()->mName.compare(Name)==0)
		{
			return TextureITR.item()->mData->getTextureMask();
		}

	SGZ::Logger.log( SGZLOG::Warning, "Texture " + Name + " does not exist!\n");
	return NULL;
}

bool MTexture::setColour ( const std::string &Name, const SGZ::RGBCOLOUR &colour )
{
	SListIterator<TextureObj*> TextureITR = mTextureList.getIterator();
	for( TextureITR.start(); TextureITR.valid(); TextureITR.forth() )
		if(TextureITR.item()->mName.compare(Name)==0)
		{
			TextureITR.item()->mData->setColour(colour);
			return true;
		}

	SGZ::Logger.log( SGZLOG::Warning, "Texture " + Name + " does not exist!\n");
	return false;
}

bool MTexture::checkExist ( const std::string &Name )
{
	SListIterator<TextureObj*> TextureITR = mTextureList.getIterator();
	for( TextureITR.start(); TextureITR.valid(); TextureITR.forth() )
		if(TextureITR.item()->mName.compare(Name)==0)
			return true;

	return false;
}

bool MTexture::blitTexture ( const std::string &Name, const SGZ::VECTOR3 &vector, const SGZ::SCALER u, const SGZ::SCALER v, const SGZ::SCALER w, const SGZ::SCALER h )
{
	SListIterator<TextureObj*> TextureITR = mTextureList.getIterator();
	for( TextureITR.start(); TextureITR.valid(); TextureITR.forth() )
		if(TextureITR.item()->mName.compare(Name)==0)
		{
			TextureITR.item()->mData->blitTexture(vector,u,v,w,h);
			return true;
		}
	SGZ::Logger.log( SGZLOG::Warning, "Texture " + Name + " does not exist!\n");
	return false;
}

bool MTexture::blitTexture ( const std::string &Name,  const float x1, const float y1, const float u1, const float v1,
												const float x2, const float y2, const float u2, const float v2,
												const float x3, const float y3, const float u3, const float v3,
												const float x4, const float y4, const float u4, const float v4,
																								const int layer )
{
	SListIterator<TextureObj*> TextureITR = mTextureList.getIterator();
	for( TextureITR.start(); TextureITR.valid(); TextureITR.forth() )
		if(TextureITR.item()->mName.compare(Name)==0)
		{
			TextureITR.item()->mData->blitTexture(   x1, y1, u1, v1,
													 x2, y2, u2, v2,
													 x3, y3, u3, v3,
													 x4, y4, u4, v4,
													 layer);
			return true;
		}
	SGZ::Logger.log( SGZLOG::Warning, "Texture " + Name + " does not exist!\n");
	return false;
}


bool MTexture::setColourKey ( const std::string &Name, const SGZ::RGBCOLOUR &key )
{
	SListIterator<TextureObj*> TextureITR = mTextureList.getIterator();
	for( TextureITR.start(); TextureITR.valid(); TextureITR.forth() )
		if(TextureITR.item()->mName.compare(Name)==0)
			TextureITR.item()->mData->setColourKey(key);


	SGZ::Logger.log( SGZLOG::Warning, "Texture " + Name + " does not exist!\n");
	return false;
}
