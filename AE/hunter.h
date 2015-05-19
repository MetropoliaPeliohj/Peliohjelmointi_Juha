#ifndef _HUNTER_H_
#define _HUNTER_H_

#include <windows.h>
#include <gl/GL.h>
#include <Box2D/Box2D.h>
#include "IAI_character.h"
#include "hunter_ai.h"
#include "IPhysable.h"
#include "IRenderable.h"
#include "IShootable.h"


/**
	Shooting villain.
*/
class Hunter : public IRenderable, public IPhysable, public IAI_Character, public IShootable
{
public:

	Hunter(int, int, int, int);
	virtual ~Hunter();

	// Renderable implementation.
	virtual void render();

	// AI_Character implementation.
	virtual void run_ai();

	// Common rendering initialization
	// for all Hunter instances.
	static int	init_rendering();
	static void	finish_rendering();

	// Moving constraints.
	int get_min_x() const { return m_min_x; }
	int get_max_x() const { return m_max_x; }

	// Sets hunter's direction
	static void setDirection(bool dir);

	// Returns right texture for displaying
	GLuint getTextureToBind();

private:

	// For rendering. Common for all Hunter instances.
	static GLuint m_dl;
	static GLuint m_tex[2];

	// Direction of the hunter
	static bool direction;

	// Decision tree for hunter AI.
	Hunter_AI_Node*	m_decision_tree;

	// Moving constraints.
	int m_min_x;
	int m_max_x;
};

#endif // _HUNTER_H_
