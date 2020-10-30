#include "Input.h"
#include <iostream>

namespace PuRe
{
	Input::Input()
	{
		this->controller_num = SDL_NumJoysticks();
		for (int i = 0; i < this->controller_num; ++i) 
		{
			this->controller[i] = SDL_JoystickOpen(i);
			this->controllerhaptic[i] = SDL_HapticOpen(i);
			SDL_HapticRumbleInit(this->controllerhaptic[i]);
			printf("Opened Joystick %i\n",i);
			printf("Joystick ID: %i\n",SDL_JoystickInstanceID(this->controller[i]));
			printf("Name: %s\n", SDL_JoystickNameForIndex(i));
			printf("Number of Axes: %d\n", SDL_JoystickNumAxes(this->controller[i]));
			printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(this->controller[i]));
			printf("Number of Balls: %d\n", SDL_JoystickNumBalls(this->controller[i]));
			std::string name = SDL_JoystickNameForIndex(i);
			if(name.compare(0,6,"XInput") == 0||name.compare(0,14,"Razer Nostromo") != 0&&name.compare(0,15,"Razer Orbweaver") != 0&&name.compare(0,14,"Razer Tartarus") != 0)
			{
				this->exist[i] = true;
			}
		}
		this->state = SDL_GetKeyboardState(NULL);
	}
	Input::~Input()
	{
		for (int i = 0; i < this->controller_num; ++i) 
		{
			Rumble(i,1.0f,10);
			SDL_HapticClose(this->controllerhaptic[i]);
			SDL_JoystickClose(this->controller[i]);
		}
	}
	void Input::CheckController()
	{
		for (int i = 0; i < this->controller_num; ++i) 
		{
			Rumble(i,1.0f,10);
			SDL_HapticClose(this->controllerhaptic[i]);
			SDL_JoystickClose(this->controller[i]);
		}
		this->controller_num = SDL_NumJoysticks();
		for (int i = 0; i < this->controller_num; ++i) 
		{
			this->controller[i] = SDL_JoystickOpen(i);
			this->controllerhaptic[i] = SDL_HapticOpen(i);
			SDL_HapticRumbleInit(this->controllerhaptic[i]);
			printf("Opened Joystick %i\n",i);
			printf("Joystick ID: %i\n",SDL_JoystickInstanceID(this->controller[i]));
			printf("Name: %s\n", SDL_JoystickNameForIndex(i));
			printf("Number of Axes: %d\n", SDL_JoystickNumAxes(this->controller[i]));
			printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(this->controller[i]));
			printf("Number of Balls: %d\n", SDL_JoystickNumBalls(this->controller[i]));
			std::string name = SDL_JoystickNameForIndex(i);
			if(name.compare(0,6,"XInput") == 0||name.compare(0,14,"Razer Nostromo") != 0&&name.compare(0,15,"Razer Orbweaver") != 0&&name.compare(0,14,"Razer Tartarus") != 0)
			{
				this->exist[i] = true;
			}
		}
		this->state = SDL_GetKeyboardState(NULL);
	}
	void Input::Rumble(unsigned short player,float strength,unsigned short length)
	{
		if(strength > 1.0f) 
			strength = 1.0f; 
		else if(strength < 0.0f) 
			strength = 0.0f;
		SDL_HapticRumblePlay(this->controllerhaptic[player],strength,length);
	}
	unsigned short Input::getControllerNum()
	{
		return this->controller_num;
		//return 1;
	}
	void Input::Update()
	{
		//Update Controller
		if(this->controller_num != SDL_NumJoysticks())
		{
			this->CheckController();
		}
		for (int i = 0; i < this->controller_num; ++i) 
		{
			std::string name = SDL_JoystickNameForIndex(i);
			//Left Stick
			C_LStick_X[i] = SDL_JoystickGetAxis(this->controller[i], 0);
			C_LStick_Y[i] = SDL_JoystickGetAxis(this->controller[i], 1);
			//Right Stick
			C_RStick_X[i] = SDL_JoystickGetAxis(this->controller[i], 2);
			C_RStick_Y[i] = SDL_JoystickGetAxis(this->controller[i], 3);
			//Get Type of Controller
			if(name.compare(0,6,"XInput") == 0)
			{
				//XBOX 360
				//Start
				if(SDL_JoystickGetButton(this->controller[i],4) == 1&&!C_Start_isPressed[i])
				{
					C_Start_isPressed[i] = true;
					C_Start_Pressed[i] = true;
				}
				else
				{
					C_Start_Pressed[i] = false;
					if(SDL_JoystickGetButton(this->controller[i],4) == 0)
						C_Start_isPressed[i] = false;
				}
				//B
				if(SDL_JoystickGetButton(this->controller[i],11) == 1&&!C_B_isPressed[i])
				{
					C_B_isPressed[i] = true;
					C_B_Pressed[i] = true;
				}
				else
				{
					C_B_Pressed[i] = false;
					if(SDL_JoystickGetButton(this->controller[i],11) == 0)
						C_B_isPressed[i] = false;
				}
				//Y
				if(SDL_JoystickGetButton(this->controller[i],13) == 1&&!C_Y_isPressed[i])
				{
					C_Y_isPressed[i] = true;
					C_Y_Pressed[i] = true;
				}
				else
				{
					C_Y_Pressed[i] = false;
					if(SDL_JoystickGetButton(this->controller[i],13) == 0)
						C_Y_isPressed[i] = false;
				}
				//X
				if(SDL_JoystickGetButton(this->controller[i],12) == 1&&!C_X_isPressed[i])
				{
					C_X_isPressed[i] = true;
					C_X_Pressed[i] = true;
				}
				else
				{
					C_X_Pressed[i] = false;
					if(SDL_JoystickGetButton(this->controller[i],12) == 0)
						C_X_isPressed[i] = false;
				}
				//A
				if(SDL_JoystickGetButton(this->controller[i],10) == 1&&!C_A_isPressed[i])
				{
					C_A_isPressed[i] = true;
					C_A_Pressed[i] = true;
				}
				else
				{
					C_A_Pressed[i] = false;
					if(SDL_JoystickGetButton(this->controller[i],10) == 0)
						C_A_isPressed[i] = false;
				}
				//RB
				if(SDL_JoystickGetButton(this->controller[i],9) == 1&&!C_RB_isPressed[i])
				{
					C_RB_isPressed[i] = true;
					C_RB_Pressed[i] = true;
				}
				else
				{
					C_RB_Pressed[i] = false;
					if(SDL_JoystickGetButton(this->controller[i],9) == 0)
						C_RB_isPressed[i] = false;
				}
				//LB
				if(SDL_JoystickGetButton(this->controller[i],8) == 1&&!C_LB_isPressed[i])
				{
					C_LB_isPressed[i] = true;
					C_LB_Pressed[i] = true;
				}
				else
				{
					C_LB_Pressed[i] = false;
					if(SDL_JoystickGetButton(this->controller[i],8) == 0)
						C_LB_isPressed[i] = false;
				}
				//LT
				C_LT_Pressed[i] = (SDL_JoystickGetAxis(this->controller[i], 4)+32767)/65534.0f;
				if(C_LT_Pressed[i] > 1.0f)
					C_LT_Pressed[i] = 1.0f;
				else if(C_LT_Pressed[i] < 0.0f)
					C_LT_Pressed[i] = 0.0f;
				C_RT_Pressed[i] = (SDL_JoystickGetAxis(this->controller[i], 5)+32767)/65534.0f;
				if(C_RT_Pressed[i] > 1.0f)
					C_RT_Pressed[i] = 1.0f;
				else if(C_RT_Pressed[i] < 0.0f)
					C_RT_Pressed[i] = 0.0f;
			}
			else if(name.compare(0,14,"Razer Nostromo") != 0&&name.compare(0,15,"Razer Orbweaver") != 0&&name.compare(0,14,"Razer Tartarus") != 0)
			{
				//Start
				if(SDL_JoystickGetButton(this->controller[i],9) == 1&&!C_Start_isPressed[i])
				{
					C_Start_isPressed[i] = true;
					C_Start_Pressed[i] = true;
				}
				else
				{
					C_Start_Pressed[i] = false;
					if(SDL_JoystickGetButton(this->controller[i],9) == 0)
						C_Start_isPressed[i] = false;
				}
				//B
				if(SDL_JoystickGetButton(this->controller[i],1) == 1&&!C_B_isPressed[i])
				{
					C_B_isPressed[i] = true;
					C_B_Pressed[i] = true;
				}
				else
				{
					C_B_Pressed[i] = false;
					if(SDL_JoystickGetButton(this->controller[i],1) == 0)
						C_B_isPressed[i] = false;
				}
				//Y
				if(SDL_JoystickGetButton(this->controller[i],0) == 1&&!C_Y_isPressed[i])
				{
					C_Y_isPressed[i] = true;
					C_Y_Pressed[i] = true;
				}
				else
				{
					C_Y_Pressed[i] = false;
					if(SDL_JoystickGetButton(this->controller[i],0) == 0)
						C_Y_isPressed[i] = false;
				}
				//X
				if(SDL_JoystickGetButton(this->controller[i],3) == 1&&!C_X_isPressed[i])
				{
					C_X_isPressed[i] = true;
					C_X_Pressed[i] = true;
				}
				else
				{
					C_X_Pressed[i] = false;
					if(SDL_JoystickGetButton(this->controller[i],3) == 0)
						C_X_isPressed[i] = false;
				}
				//A
				if(SDL_JoystickGetButton(this->controller[i],2) == 1&&!C_A_isPressed[i])
				{
					C_A_isPressed[i] = true;
					C_A_Pressed[i] = true;
				}
				else
				{
					C_A_Pressed[i] = false;
					if(SDL_JoystickGetButton(this->controller[i],2) == 0)
						C_A_isPressed[i] = false;
				}
				//RB
				if(SDL_JoystickGetButton(this->controller[i],5) == 1&&!C_RB_isPressed[i])
				{
					C_RB_isPressed[i] = true;
					C_RB_Pressed[i] = true;
				}
				else
				{
					C_RB_Pressed[i] = false;
					if(SDL_JoystickGetButton(this->controller[i],5) == 0)
						C_RB_isPressed[i] = false;
				}
				//LB
				if(SDL_JoystickGetButton(this->controller[i],4) == 1&&!C_LB_isPressed[i])
				{
					C_LB_isPressed[i] = true;
					C_LB_Pressed[i] = true;
				}
				else
				{
					C_LB_Pressed[i] = false;
					if(SDL_JoystickGetButton(this->controller[i],4) == 0)
						C_LB_isPressed[i] = false;
				}
				//LT
				if(SDL_JoystickGetButton(this->controller[i],6) == 1)
				{
					C_LT_Pressed[i] = 1;
				}
				else
				{
					C_LT_Pressed[i] = 0;
				}
				//RT
				if(SDL_JoystickGetButton(this->controller[i],7) == 1)
				{
					C_RT_Pressed[i] = 1;
				}
				else
				{
					C_RT_Pressed[i] = 0;
				}
			}
			for (int j = 0; j < 15; ++j) 
			{
				this->ButtonPress[i][j] = SDL_JoystickGetButton(this->controller[i],j) == 1;
				/*			if(this->ButtonPress[i][j])
				printf("BUTTON PRESS: %i\n",j);*/
			}

			//i//
		}
		if(this->state[SDL_SCANCODE_Q] != 0&&!Q_isPressed)
		{
			Q_isPressed = true;
			Q_Pressed = true;
		}
		else
		{
			Q_Pressed = false;
			if(this->state[SDL_SCANCODE_Q] == 0)
				Q_isPressed = false;
		}
		if(this->state[SDL_SCANCODE_E] != 0&&!E_isPressed)
		{
			E_isPressed = true;
			E_Pressed = true;
		}
		else
		{
			E_Pressed = false;
			if(this->state[SDL_SCANCODE_E] == 0)
				E_isPressed = false;
		}
		if(this->state[SDL_SCANCODE_W] != 0&&!W_isPressed)
		{
			W_isPressed = true;
			W_Pressed = true;
		}
		else
		{
			W_Pressed = false;
			if(this->state[SDL_SCANCODE_W] == 0)
				W_isPressed = false;
		}
		if(this->state[SDL_SCANCODE_A] != 0&&!A_isPressed)
		{
			A_isPressed = true;
			A_Pressed = true;
		}
		else
		{
			A_Pressed = false;
			if(this->state[SDL_SCANCODE_A] == 0)
				A_isPressed = false;
		}
		if(this->state[SDL_SCANCODE_S] != 0&&!S_isPressed)
		{
			S_isPressed = true;
			S_Pressed = true;
		}
		else
		{
			S_Pressed = false;
			if(this->state[SDL_SCANCODE_S] == 0)
				S_isPressed = false;
		}
		if(this->state[SDL_SCANCODE_D] != 0&&!D_isPressed)
		{
			D_isPressed = true;
			D_Pressed = true;
		}
		else
		{
			D_Pressed = false;
			if(this->state[SDL_SCANCODE_D] == 0)
				D_isPressed = false;
		}
		//Check if escape is pressed ONCE
		if(this->state[SDL_SCANCODE_ESCAPE] != 0&&!esc_isPressed)
		{
			esc_isPressed = true;
			esc_Pressed = true;
		}
		else
		{
			esc_Pressed = false;
			if(this->state[SDL_SCANCODE_ESCAPE] == 0)
				esc_isPressed = false;
		}
		//Check if Arrows are pressed
		if(this->state[SDL_SCANCODE_UP] != 0&&!up_isPressed)
		{
			up_isPressed = true;
			up_Pressed = true;
		}
		else
		{
			up_Pressed = false;
			if(this->state[SDL_SCANCODE_UP] == 0)
				up_isPressed = false;
		}
		if(this->state[SDL_SCANCODE_LEFT] != 0&&!left_isPressed)
		{
			left_isPressed = true;
			left_Pressed = true;
		}
		else
		{
			left_Pressed = false;
			if(this->state[SDL_SCANCODE_LEFT] == 0)
				left_isPressed = false;
		}
		if(this->state[SDL_SCANCODE_DOWN] != 0&&!down_isPressed)
		{
			down_isPressed = true;
			down_Pressed = true;
		}
		else
		{
			down_Pressed = false;
			if(this->state[SDL_SCANCODE_DOWN] == 0)
				down_isPressed = false;
		}
		if(this->state[SDL_SCANCODE_RIGHT] != 0&&!right_isPressed)
		{
			right_isPressed = true;
			right_Pressed = true;
		}
		else
		{
			right_Pressed = false;
			if(this->state[SDL_SCANCODE_RIGHT] == 0)
				right_isPressed = false;
		}

		//Check if f1 is pressed ONCE
		if(this->state[SDL_SCANCODE_F11] != 0&&!f11_isPressed)
		{
			f11_isPressed = true;
			f11_Pressed = true;
		}
		else
		{
			f11_Pressed = false;
			if(this->state[SDL_SCANCODE_F11] == 0)
				f11_isPressed = false;
		}
	}
}