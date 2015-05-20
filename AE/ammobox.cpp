#include <list>
#include <windows.h>
#include <math.h>
#include <gl/glew.h>
#include <gl/GL.h>
#include <SDL.h>
#include <SDL_image.h>
#include "ae.h"
#include "world.h"
#include "ammobox.h"
#include "ammobox_list.h"
#include "collision.h"

GLuint Ammobox::m_dl			= 0;
GLuint Ammobox::m_tex			= 0;

/**
	Ctor.
*/
Ammobox::Ammobox(int x, int y) : _x(x), _y(y)
{
	// Static body
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(
		x / (float)PHYS_SCALE,
		y / (float)PHYS_SCALE);
	m_body = World::get()->CreateBody(&bodyDef);
	b2PolygonShape box;
	box.SetAsBox(
		(AMMOBOX_WIDTH / 2.0) / (float)PHYS_SCALE,
		(AMMOBOX_HEIGHT / 2.0) / (float)PHYS_SCALE);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &box;
	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);
	/*
	Ammobox::bodies.push_back(m_body);
	Ammobox::ammoboxes.push_back(this);
	*/

	ammobox_list::get()->push_back_unique(this);
}

/**
	Dtor.
*/
Ammobox::~Ammobox()
{
}

/**
	Initializes ammobox for rendering.

	Returns 1 for success, 0 otherwise.
*/
int Ammobox::init_rendering()
{

	Ammobox::m_dl = glGenLists(1);
	glNewList(Ammobox::m_dl, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.0); glVertex3f(-AMMOBOX_WIDTH / 2.0, AMMOBOX_HEIGHT / 2.0, 0.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(AMMOBOX_WIDTH / 2.0, AMMOBOX_HEIGHT / 2.0, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(AMMOBOX_WIDTH / 2.0, -AMMOBOX_HEIGHT / 2.0, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-AMMOBOX_WIDTH / 2.0, -AMMOBOX_HEIGHT / 2.0, 0.0);
	glEnd();
	glEndList();

	//
	// Textures.
	//
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &m_tex);
	glBindTexture(GL_TEXTURE_2D, m_tex);
	SDL_Surface *teximage = IMG_Load("ammobox.png");
	if (!teximage)
		return 0;
	gluBuild2DMipmaps(
		GL_TEXTURE_2D,
		GL_RGBA,
		teximage->w,
		teximage->h,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		teximage->pixels
		);
	SDL_FreeSurface(teximage);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glDisable(GL_TEXTURE_2D);
	return (glGetError() == GL_NO_ERROR);

}

/**
Render ammobox.
*/
void Ammobox::render()
{
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	b2Vec2 pos = m_body->GetPosition();
	float angle = RAD2DEG(m_body->GetAngle());
	glTranslatef(pos.x * PHYS_SCALE, pos.y * PHYS_SCALE, 1.0);
	glBindTexture(GL_TEXTURE_2D, m_tex);
	glCallList(m_dl);
	glDisable(GL_TEXTURE_2D);
}

/**
Rendering clean-up.
*/
void Ammobox::finish_rendering()
{
	glDeleteLists(Ammobox::m_dl, 1);
	Ammobox::m_dl = 0;
}