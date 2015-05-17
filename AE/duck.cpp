#include <windows.h>
#include <math.h>
#include <gl/glew.h>
#include <gl/GL.h>
#include <SDL.h>
#include <SDL_image.h>
#include "ae.h"
#include "world.h"
#include "duck.h"
#include "collision.h"

GLuint Duck::m_dl		= 0;
GLuint Duck::m_tex = 0;
Duck*  Duck::m_instance = 0;


/**
	(Singleton) instance access.
*/
Duck* Duck::get_duck()
{
	return Duck::m_instance;
}


/**
	Ctor.
*/
Duck::Duck(int x, int y) : _x(x), _y(y)
{

	/*
		b2CircleShape circleShape;
	circleShape.m_radius = DUCK_RADIUS / (float)PHYS_SCALE;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	
	*/
	// Dynamic body for physics.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(
		x / (float)PHYS_SCALE,
		y / (float)PHYS_SCALE);
	m_body = World::get()->CreateBody(&bodyDef);
	b2PolygonShape box;
	box.SetAsBox(
		(HUNTER_WIDTH / 2.0) / (float)PHYS_SCALE,
		(HUNTER_HEIGHT / 2.0) / (float)PHYS_SCALE);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &box;
	fixtureDef.density = DUCK_DENSITY;
	fixtureDef.friction = DUCK_FRICTION;
	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);

	// Set (singleton) instance.
	Duck::m_instance = this;
}


/**
	Dtor.
*/
Duck::~Duck()
{
}


/**
	Initializes duck for rendering.

	Returns 1 for success, 0 otherwise.
*/
int	Duck::init()
{
	if (Duck::m_dl)
		return 1;

	//
	// Prepare a display list for rendering.
	// TODO: NOW JUST A PLACEHOLDER (CIRCLE).
	//
	Duck::m_dl = glGenLists(1);
	glNewList(Duck::m_dl, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.0); glVertex3f(-DUCK_WIDTH / 2.0, DUCK_HEIGHT / 2.0, 0.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(DUCK_WIDTH / 2.0, DUCK_HEIGHT / 2.0, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(DUCK_WIDTH / 2.0, -DUCK_HEIGHT / 2.0, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-DUCK_WIDTH/ 2.0, -DUCK_HEIGHT / 2.0, 0.0);
	glEnd();
	glEndList();

	//
	// Textures.
	//
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &m_tex);
	glBindTexture(GL_TEXTURE_2D, m_tex);
	SDL_Surface *teximage = IMG_Load("duck.png");
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



	/*

																							// LEVEL.CPP TEKSTUROINTI:
																							glEnable(GL_TEXTURE_2D);
																							glGenTextures(1, &m_tex);
																							glBindTexture(GL_TEXTURE_2D, m_tex);
																							SDL_Surface *teximage = IMG_Load(m_image_file_name.c_str());
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

				// HUNTER.CPP TEKSTUROINTI
				glEnable(GL_TEXTURE_2D);
				glGenTextures(1, &m_tex);
				glBindTexture(GL_TEXTURE_2D, m_tex);
				SDL_Surface *teximage = IMG_Load("chrome.png");
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
						
						
						glBegin(GL_LINE_LOOP);
			for (int i=0; i < 360; i++)
			{
				glVertex3f(
					cos(DEG2RAD(i)) * DUCK_RADIUS,
					sin(DEG2RAD(i)) * DUCK_RADIUS,
					0.0);
			}
			glVertex3f(0.0, 0.0, 0.0);




			glBegin(GL_LINE_LOOP);
			for (int i=0; i < 360; i++)
			{
			glVertex3f(
			cos(DEG2RAD(i)) * DUCK_RADIUS,
			sin(DEG2RAD(i)) * DUCK_RADIUS,
			0.0);
			}
			glVertex3f(0.0, 0.0, 0.0);

	*/

	return (glGetError() == GL_NO_ERROR);
}


/**
	Render duck.
*/
void Duck::render()
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
void Duck::fini()
{
	glDeleteLists(Duck::m_dl, 1);
	Duck::m_dl = 0;
}


/**
	Apply force to move the duck left.
*/
void Duck::left()
{
	b2Vec2 pos = m_body->GetPosition();
	
	m_body->ApplyForceToCenter(b2Vec2(DUCK_FORCE_LEFT, 0));
	
}


/**
	Apply force to move the duck right.
*/
void Duck::right()
{
	m_body->ApplyForceToCenter(b2Vec2(DUCK_FORCE_RIGHT, 0));
}


/**
	Apply force to make the duck jump/fly.
*/
void Duck::jump()
{
	if (Contact_Listener::getContactState() == 1){
		m_body->ApplyForceToCenter(b2Vec2(0, DUCK_FORCE_JUMP));
	}
}


/**
	Set modelview matrix so that the duck is centralized
	and scaling applied.
*/
void Duck::set_camera_to_duck() const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//
	// Change scaling according to height. A better idea would be
	// to change scaling according to velocity.
	//
	// For constant scale, set scaling = GF_SCALE.
	//
	b2Vec2 pos = m_body->GetPosition();
	float scaling = (DUCK_ORIG_Y - pos.y * PHYS_SCALE) / DUCK_ORIG_Y;
	if (scaling < 0.1)
		scaling = 0.1;
	if (scaling > 1.0)
		scaling = 1.0;

	//
	// Center the duck.
	//
	gluLookAt(
		pos.x * PHYS_SCALE * scaling - WIDTH / 2,
		pos.y * PHYS_SCALE * scaling - HEIGHT / 2,
		1,
		pos.x * PHYS_SCALE * scaling - WIDTH / 2,
		pos.y * PHYS_SCALE * scaling - HEIGHT / 2,
		0,
		0,
		1,
		0
		);

	glScalef(scaling, scaling, 1);
}
