#ifndef _GRAPHICS_SYSTEM_H_
#define _GRAPHICS_SYSTEM_H_

// Rather SDL specific, but lack of time dictates the needs!

#include <SDL/SDL.h>
#include <SDL/SDL_framerate.h>

class GraphicsCamera;
class GraphicsSystem
{
	public:
		~GraphicsSystem();
	
		//! Creates or returns the current active instance.
		static GraphicsSystem& instance();
		
		//! Initialise the Graphics
		void initialise(const Uint32 width, const Uint32 height, const Uint32 bpp);
		
		//! Render everything to a Camera
		void render(GraphicsCamera* const graphicsCamera);
		
	private:
		GraphicsSystem();
		
		static GraphicsSystem* instance_;	//!< Active instance
		Uint32 width_;
		Uint32 height_;
		Uint32 bpp_;
		
		SDL_Surface* screen_; //!< Actual screen surface to draw on.
		FPSmanager fpsManager_;
};

#endif
