#ifndef _AMMOBOX_H_
#define _AMMOBOX_H_

#include <windows.h>
#include <gl/GL.h>
#include <Box2D/Box2D.h>
#include "IPhysable.h"
#include "IRenderable.h"

/**
	Collectable ammoboxes
*/

class Ammobox : public IRenderable, public IPhysable
{

public:

	Ammobox(int, int);
	virtual ~Ammobox();

	// Renderable implementation
	virtual void render();

	// Common rendering initialization
	// for all Ammo instances.
	static int init_rendering();
	static void finish_rendering();

private:

	// Coordinates
	int _x;
	int _y;

	// For rendering. Common for all ammobox instances.
	static GLuint m_dl;
	static GLuint m_tex;

};

#endif // _AMMOBOX_H