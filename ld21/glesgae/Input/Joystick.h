#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include "Controller.h"
#include "ControllerTypes.h"

#include <vector>

namespace GLESGAE
{
	class InputSystem;
	namespace Controller
	{
		class JoystickController : public CommonController
		{
			friend class GLESGAE::InputSystem;
			public:
				JoystickController(const Controller::Id controllerId, const Axes axes, const Button buttons)
				: CommonController(Joystick, controllerId)
				, mAxes(axes)
				, mButtons(buttons)
				{
					
				}
				
				/// Get the value of the specified axis
				float getAxis(const Axes axis) const
				{
					// TODO: actual error checking
					return mAxes[axis];
				}
				
				/// Get the value of the specified button
				float getButton(const Button button) const
				{
					// TODO: actual error checking
					return mButtons[button];
				}
				
				/// Get amount of buttons
				Button getNumButtons() const { return mButtons.size(); }
				
				/// Get amount of axes
				Axes getNumAxes() const { return mAxes.size(); }
				
			protected:
				/// Set Axis data
				void setAxis(const Axes axis, const float data)
				{
					// TODO: actual error checking
					mAxes[axis] = data;
				}
				
				/// Set Button data
				void setButton(const Button button, const float data)
				{
					// TODO: actual error checking
					mButtons[button] = data;
				}
				
			private:
				std::vector<float> mAxes;
				std::vector<float> mButtons;
		};
	}
}

#endif