#ifndef _DUCK_H_
#define _DUCK_H_

#include <windows.h>
#include <gl/GL.h>
#include "IPhysable.h"
#include "IRenderable.h"
#include "IShootable.h"


/**
	Player controlled duck.
*/
class Duck : public IRenderable, public IPhysable, public IShootable
{
public:

	bool goLeft;
	bool goRight;
	bool goJump;
	bool doShoot;

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
	int is_alive() const	{ return m_is_alive; }
	void kill()				{ m_is_alive = 0; }
	void handle_inputs();
	void shoot();

	// Camera will follow the duck.
	void set_camera_to_duck() const;

	// Returns right texture for displaying
	GLuint getTextureToBind();

	// Sets duck's jumping state
	void setJumpingState();

private:

	// Coordinates (this will change once
	// we get physics in).
	int _x;
	int _y;

	// State of duck's direction and jumping.
	static bool direction;
	static bool jumping;
	static bool moving;

	// For rendering. Common for all Duck instances.
	static GLuint m_dl;
	static GLuint m_tex[4];

	// For (singleton) instance access.
	static Duck* m_instance;

	// Duck health, set to 0 if hit.
	int m_is_alive;
};

#endif // _DUCK_H_
