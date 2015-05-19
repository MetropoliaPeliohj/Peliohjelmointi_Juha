#include <windows.h>
#include <math.h>
#include <gl/glew.h>
#include <gl/GL.h>
#include <SDL.h>
#include <SDL_image.h>
#include <Box2D/Box2D.h>
#include "ae.h"
#include "world.h"
#include "bullet.h"

GLuint Bullet::m_dl		= 0;
GLuint Bullet::m_tex	= 0;

/*
	Ctor.
*/
Bullet::Bullet(int x, int y, float angle, float force)
{
	// Dynamic body for physics.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(
		x / (float)PHYS_SCALE, 
		y / (float)PHYS_SCALE);

	// Set as a bullet for continuous collision detection.
	bodyDef.bullet = true;

	m_body = World::get()->CreateBody(&bodyDef);
	b2CircleShape circleShape;
	circleShape.m_radius = BULLET_RADIUS / (float)PHYS_SCALE;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = BULLET_DENSITY;
	fixtureDef.friction = BULLET_FRICTION;
	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);

	// Fire the bullet!
	m_body->ApplyForceToCenter(
		b2Vec2(
			force * cos(DEG2RAD(angle)), 
			force * sin(DEG2RAD(angle))
		)
	);
}


/*
	Dtor.
*/
Bullet::~Bullet()
{
}


/*
	Renderable initialization.

	Returns 1 for success, 0 otherwise.
*/
int	Bullet::init_rendering()
{
	if (Bullet::m_dl)
		return 1;

	//
	// Prepare a display list for rendering.
	//
	Bullet::m_dl = glGenLists(1);
	glNewList(Bullet::m_dl, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.0); glVertex3f(-BULLET_WIDTH / 2.0, BULLET_HEIGHT / 2.0, 0.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(BULLET_WIDTH / 2.0, BULLET_HEIGHT / 2.0, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(BULLET_WIDTH / 2.0, -BULLET_HEIGHT / 2.0, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-BULLET_WIDTH / 2.0, -BULLET_HEIGHT / 2.0, 0.0);
	glEnd();
	glEndList();

	//
	// Textures.
	//
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &m_tex);
	glBindTexture(GL_TEXTURE_2D, m_tex);
	SDL_Surface *teximage = IMG_Load("bullet.png");
	if (!teximage)
		return 0;
	gluBuild2DMipmaps(
		GL_TEXTURE_2D,		// texture to specify
		GL_RGBA,			// internal texture storage format
		teximage->w,		// texture width
		teximage->h,		// texture height
		GL_RGBA,			// pixel format (possibly RGBA)
		GL_UNSIGNED_BYTE,	// color component format
		teximage->pixels	// pointer to texture image
		);
	SDL_FreeSurface(teximage);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glDisable(GL_TEXTURE_2D);
	return (glGetError() == GL_NO_ERROR);
}


/*
	Render Bullet.
*/
void Bullet::render()
{
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	b2Vec2 pos = m_body->GetPosition();
	float angle = m_body->GetAngle() * 57.2957795;
	glTranslatef(pos.x * PHYS_SCALE, pos.y * PHYS_SCALE, 0.5);
	glBindTexture(GL_TEXTURE_2D, m_tex);
	glRotatef(angle, 0.0, 0.0, 1.0);
	glCallList(m_dl);
	glDisable(GL_TEXTURE_2D);
}

/*
	Renderable finalization.
*/
void Bullet::finish_rendering()
{
	glDeleteLists(m_dl, 1);
	Bullet::m_dl = 0;
}

