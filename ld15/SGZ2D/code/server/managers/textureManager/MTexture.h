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
	\file MTexture.h
	\brief The Texture Manager

*/

#ifndef _MTEXTURE_H_
#define _MTEXTURE_H_

#include "../../../typedefs.h"
#include "../../../client/renderer/texture/OTexture.h"
#include "../../../common/data/CSLinkedlist.h"

class TextureObj
{
	public:

		std::string mName;
		OTexture *mData;

		TextureObj()
		:   mName(),
			mData(new OTexture)
		{
			/* nope */
		};

		TextureObj( const TextureObj& )
		:   mName(),
			mData()
		{
		}

		TextureObj operator=( const TextureObj& )
		{
			throw("TODO: TextureObj operator=");
		}

		~TextureObj()
		{
			mData->deleteTexture();
			delete mData;
		};
};

class MTexture
{
	public:
		MTexture();
		~MTexture();

		bool	addTexture( const std::string &pName, const std::string &pFilename );
		bool	addTexMask( const std::string &pName, const std::string &pMaskname );
		bool	delTexture( const std::string &pName );
		TextureObj* getObj( const std::string &pName );
		void*   getTexture( const std::string &pName );
		void*   getTextureMask( const std::string &pName);
		bool	blitTexture( const std::string &pName, const SGZ::VECTOR3 &pVector, const SGZ::SCALER u, const SGZ::SCALER v, const SGZ::SCALER w, const SGZ::SCALER h );
		bool	blitTexture( const std::string &pName,  const float x1, const float y1, const float u1, const float v1,
												const float x2, const float y2, const float u2, const float v2,
												const float x3, const float y3, const float u3, const float v3,
												const float x4, const float y4, const float u4, const float v4,
																								const int layer );

		bool	setColour ( const std::string &pName, const SGZ::RGBCOLOUR &pColour );
		bool	setColourKey ( const std::string &pName, const SGZ::RGBCOLOUR &pKey );
		bool	checkExist( const std::string &pName );

	private:
		SLinkedList<TextureObj*> mTextureList;
};

#endif
