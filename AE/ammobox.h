#ifndef _AMMOBOX_H_
#define _AMMOBOX_H_

#include <list>
#include <windows.h>
#include <gl/GL.h>
#include <Box2D/Box2D.h>
#include "IPhysable.h"
#include "IRenderable.h"

/**
	Collectable ammoboxes
*/

class Ammobox : public IRenderable, public IPhysable, public std::list<b2Body*>, public std::list<Ammobox*>
{

public:

	Ammobox(int, int);
	virtual ~Ammobox();

	// Renderable implementation
	virtual void render();

	
	static list<b2Body*> bodies;
	static list<Ammobox*> ammoboxes;
	

	// Common rendering initialization
	// for all Ammo instances.
	static int init_rendering();
	static void finish_rendering();

	int is_alive() const	{ return m_exists; }
	void kill()				{ m_exists = 0; }

private:

	// Coordinates
	int _x;
	int _y;

	// For rendering. Common for all ammobox instances.
	static GLuint m_dl;
	static GLuint m_tex;

	int m_exists;

};

#endif // _AMMOBOX_H