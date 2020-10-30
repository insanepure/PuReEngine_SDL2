#pragma once

#ifdef __linux__
//LINUX
#include <SDL2/SDL.h>
#elif _WIN32
//Windows
#include <SDL.h>
#elif _APPLE_
#include "TargetConditionals.h"
#ifdef TARGET_OS_MAC
//MAC
#endif
#endif
namespace PuRe
{
	class Input
	{
	public:
		Input();
		~Input();
		void CheckController();
		void Update();
		void Rumble(unsigned short player,float strength,unsigned short length);
		//KeyBoard
		bool esc_Pressed,esc_isPressed;
		bool f11_Pressed,f11_isPressed;
		bool up_isPressed,up_Pressed;
		bool left_isPressed,left_Pressed;
		bool down_isPressed,down_Pressed;
		bool right_isPressed,right_Pressed;
		bool W_isPressed,W_Pressed;
		bool A_isPressed,A_Pressed;
		bool S_isPressed,S_Pressed;
		bool D_isPressed,D_Pressed;
		bool Q_isPressed,Q_Pressed;
		bool E_isPressed,E_Pressed;
		//Controllermapping
		bool ButtonPress[4][15];
		bool C_Start_Pressed[4],C_Start_isPressed[4];
		bool C_A_Pressed[4],C_A_isPressed[4];
		bool C_X_Pressed[4],C_X_isPressed[4];
		bool C_Y_Pressed[4],C_Y_isPressed[4];
		bool C_B_Pressed[4],C_B_isPressed[4];
		bool C_LB_Pressed[4],C_LB_isPressed[4];
		bool C_RB_Pressed[4],C_RB_isPressed[4];

		float C_RT_Pressed[4];
		float C_LT_Pressed[4];
		Sint16 C_RStick_X[4];
		Sint16 C_RStick_Y[4];
		Sint16 C_LStick_X[4];
		Sint16 C_LStick_Y[4];
		unsigned short getControllerNum();
		bool exist[4];

	private:
		const Uint8* state;
		SDL_Joystick* controller[4];
		SDL_Haptic* controllerhaptic[4];
		unsigned short controller_num;

	};
}