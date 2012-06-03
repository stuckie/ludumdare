#ifndef _GRAPHICS_CAMERA_2D_H_
#define _GRAPHICS_CAMERA_2D_H_

#include "Math.h"

class GraphicsCamera2D : public GraphicsCamera
{
	public:
		GraphicsCamera2D();
		~GraphicsCamera2D();
		
	private:
		Vector2D position_;
		ViewPort2D viewport_;

};

#endif
