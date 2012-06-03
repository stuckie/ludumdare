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

#ifndef _BUTTON_STATES_H_
#define _BUTTON_STATES_H_

#include <string>

class OTexture;

class ButtonStates
{
	public:
		ButtonStates()
		: mStateName()
		, mTexture(0)
		{
			/* nope */
		};

		ButtonStates(const ButtonStates&)
		: mStateName()
		, mTexture(0)
		{
			throw("TODO: ButtonStates");
		};

		ButtonStates operator=(const ButtonStates&)
		{
			throw("TODO: ButtonStates");
		};


		~ButtonStates()
		{
			/* nope */
		};

		void setName(const std::string &pName) { mStateName = pName; };
		const std::string& getName() const { return mStateName; };

		void setTexture(OTexture &pTexture) { mTexture = &pTexture; };
		const OTexture* getTexture() { return mTexture; };

	private:
		std::string mStateName;
		OTexture *mTexture;
};

#endif