#ifndef _INPUT_H_
#define _INPUT_H_

#include <SDL.h>

class input
{

private:

	const Uint8* keyArray;
	SDL_Event event;

public:

	input()
	{
		SDL_PumpEvents();
		keyArray = SDL_GetKeyboardState(NULL);
	}

	void update()
	{
		SDL_PumpEvents();
		keyArray = SDL_GetKeyboardState(NULL);
	}

	bool isKeyDown(SDL_Keycode keyCode)
	{
		SDL_Scancode code = SDL_GetScancodeFromKey(keyCode);
		if (keyArray[code] == 1)
		{
			return true;
		}
		return false;
	}

	SDL_Event getEvent()
	{
		return event;
	}


};

#endif