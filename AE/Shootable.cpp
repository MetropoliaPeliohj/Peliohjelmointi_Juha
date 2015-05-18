#include <math.h>
#include <stdlib.h>
#include <SDL.h>
#include "Shootable.h"
#include "Bullet.h"
#include "ae.h"
#include "render_list.h"


/**
	Function checks if shot delay passed and if yes than shoots.
*/
void Shootable::shoot(int x, int y, float angle, float force, unsigned int max_shot_delay)
{
	unsigned int delta = SDL_GetTicks() - lastTimeShotTimestamp;

	if (delta >= max_shot_delay)
	{
		// Create a new bullet, add to the render list and update lastTimeShotTimestamp.
		Bullet* bullet = new Bullet(
			x,
			y,
			angle,
			force
			);

		Render_List::get()->push_back(bullet);
		lastTimeShotTimestamp = SDL_GetTicks();
	}
	
}