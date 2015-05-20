#ifndef _DUCK_H_
#define _DUCK_H_

#include <windows.h>
#include <gl/GL.h>
#include "IPhysable.h"
#include "IRenderable.h"
#include "IShootable.h"
#include "IHealthable.h"
#include "ICharacter.h"


/**
	Player controlled duck.
*/
class Duck : public IRenderable, public ICharacter
{
public:

	bool goLeft;
	bool goRight;
	bool goJump;
	bool doShoot;
	bool raiseAngle;
	bool lowerAngle;
	
	Duck(int, int);
	virtual ~Duck();

	// Access to (singleton) instance.
	static Duck* get_duck();

	// Renderable implementation.
	virtual void render();

	// Rendering initialization.
	static int	init_rendering();
	static void	finish_rendering();

	// Duck control and health.
	void left();
	void right();
	void jump();
	void handle_inputs();
	void shoot();
	float getAngle()		{ return shootingAngle; }

	// Camera will follow the duck.
	void set_camera_to_duck() const;

	// Returns right texture for displaying
	GLuint getTextureToBind();

	// Sets duck's jumping state
	void setJumpingState();

	void increaseAngle();
	void decreaseAngle();

private:

	// Coordinates (this will change once
	// we get physics in).
	int _x;
	int _y;

	// State of duck's direction and jumping.
	static bool direction;
	static bool jumping;
	static unsigned char shoot_direction;
	static bool moving;
	static float shootingAngle;

	// For rendering. Common for all Duck instances.
	static GLuint m_dl;
	static GLuint m_tex[4];

	// For (singleton) instance access.
	static Duck* m_instance;
};

#endif // _DUCK_H_
