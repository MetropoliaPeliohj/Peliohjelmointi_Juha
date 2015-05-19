#ifndef _BULLET_H_
#define _BULLET_H_

#include <windows.h>
#include <gl/GL.h>
#include <Box2D/Box2D.h>
#include "IPhysable.h"
#include "IRenderable.h"


/**
	Bullet, fired by hunters.
*/
class Bullet : public IRenderable, public IPhysable
{
public:

	Bullet(int, int, float, float);
	virtual ~Bullet();

	// Renderable implementation.
	virtual void render();

	// Common rendering initialization
	// for all Bullet instances.
	static int	init_rendering();
	static void	finish_rendering();

private:

	// Display List for rendering Bullets.
	// Common for all Bullet instances.
	static GLuint m_dl;
	static GLuint m_tex;

};

#endif // _BULLET_H_
