#ifndef _GRAPHIC_OBJECT_H_
#define _GRAPHIC_OBJECT_H_

#include <string>

#include "Math.h"

class GraphicObject
{
	public:
		GraphicObject() : size_(0.0F, 0.0F) {}
		virtual ~GraphicObject() {}
		
		//! Load function which all Graphic Objects must fill in.
		virtual void load(const std::string& name) = 0;
		
		//! Set Size of Graphic
		const Vector2D& readSize() const { return size_; }
		Vector2D& writeSize() { return size_; }
		
	private:
		Vector2D size_;
};

#endif
