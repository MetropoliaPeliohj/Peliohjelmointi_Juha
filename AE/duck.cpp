#include <windows.h>
#include <math.h>
#include <gl/glew.h>
#include <gl/GL.h>
#include <SDL.h>
#include <SDL_image.h>
#include "ae.h"
#include "log.h"
#include "world.h"
#include "duck.h"
#include "collision.h"
#include "Character_list.h"


GLuint Duck::m_dl				= 0;
GLuint Duck::m_tex[4]			= { 0, 0, 0, 0 };
Duck*  Duck::m_instance			= 0;
bool Duck::direction			= 1;
bool Duck::jumping				= 0;
unsigned char Duck::shoot_direction = 1;
float shootingAngle				= 25.0f;

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

	Log::log(0, "Ankka luotu");
	Character_list::get()->push_back_unique(this);
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
int	Duck::init_rendering()
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
	glGenTextures(4, m_tex);
	glBindTexture(GL_TEXTURE_2D, m_tex[0]);
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

	glBindTexture(GL_TEXTURE_2D, m_tex[1]);
	SDL_Surface *teximage2 = IMG_Load("duck2.png");
	if(!teximage2)
		return 0;
	gluBuild2DMipmaps(
		GL_TEXTURE_2D,		// texture to specify
		GL_RGBA,			// internal texture storage format
		teximage2->w,		// texture width
		teximage2->h,		// texture height
		GL_RGBA,			// pixel format (possibly RGBA)
		GL_UNSIGNED_BYTE,	// color component format
		teximage2->pixels	// pointer to texture image
		);
	SDL_FreeSurface(teximage2);

	glBindTexture(GL_TEXTURE_2D, m_tex[2]);
	SDL_Surface *teximage3 = IMG_Load("duck3.png");
	if (!teximage3)
		return 0;
	gluBuild2DMipmaps(
		GL_TEXTURE_2D,		// texture to specify
		GL_RGBA,			// internal texture storage format
		teximage3->w,		// texture width
		teximage3->h,		// texture height
		GL_RGBA,			// pixel format (possibly RGBA)
		GL_UNSIGNED_BYTE,	// color component format
		teximage3->pixels	// pointer to texture image
		);
	SDL_FreeSurface(teximage3);

	glBindTexture(GL_TEXTURE_2D, m_tex[3]);
	SDL_Surface *teximage4 = IMG_Load("duck4.png");
	if (!teximage4)
		return 0;
	gluBuild2DMipmaps(
		GL_TEXTURE_2D,		// texture to specify
		GL_RGBA,			// internal texture storage format
		teximage4->w,		// texture width
		teximage4->h,		// texture height
		GL_RGBA,			// pixel format (possibly RGBA)
		GL_UNSIGNED_BYTE,	// color component format
		teximage4->pixels	// pointer to texture image
		);
	SDL_FreeSurface(teximage4);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glDisable(GL_TEXTURE_2D);
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
	Duck::setJumpingState();
	float angle = RAD2DEG(m_body->GetAngle());
	glTranslatef(pos.x * PHYS_SCALE, pos.y * PHYS_SCALE, 1.0);
	glBindTexture(GL_TEXTURE_2D, Duck::getTextureToBind());
	glCallList(m_dl);
	glDisable(GL_TEXTURE_2D);
}


/**
	Rendering clean-up.
*/
void Duck::finish_rendering()
{
	glDeleteLists(Duck::m_dl, 1);
	Duck::m_dl = 0;
}


/**
	Apply force to move the duck left.
*/
void Duck::left()
{
	direction = 0;
	shoot_direction = -1;
	m_body->ApplyForceToCenter(b2Vec2(DUCK_FORCE_LEFT, 0));
}


/**
	Apply force to move the duck right.
*/
void Duck::right()
{
	direction = 1;
	shoot_direction = 1;
	m_body->ApplyForceToCenter(b2Vec2(DUCK_FORCE_RIGHT, 0));
}


/**
	Apply force to make the duck jump/fly.
*/
void Duck::jump()
{
	// if the number of contacts if more than 0, then jump!
	 if (m_body->GetContactList() != 0)
		m_body->ApplyForceToCenter(b2Vec2(0, DUCK_FORCE_JUMP));
		jumping = 1;
}

/**
	Try shooting
*/
void Duck::shoot()
{
	float duck_x = this->get_body()->GetPosition().x;
	float duck_y = this->get_body()->GetPosition().y;

	float duck_x_pScale = duck_x * PHYS_SCALE;
	float duck_y_pScale = duck_y * PHYS_SCALE;

	/*if (shoot_direction == -1) duck_x_pScale -= (DUCK_WIDTH*PHYS_SCALE);
	else duck_x_pScale += (DUCK_WIDTH * PHYS_SCALE);*/

	float angle = getAngle();
	printf("angle: %f", angle);
	if (direction == 0){
		angle = getAngle() + 90.0f;
		duck_x_pScale = duck_x_pScale - 400;
	}
	this->try_shoot(
		duck_x_pScale + 100,
		duck_y_pScale,
		angle,
		DUCK_BULLET_FORCE,
		DUCK_SHOOTDELAYMS
		);
}
void Duck::handle_inputs()
{
	if (this->goLeft) left();
	if (this->goRight) right();
	if (this->goJump) jump();
	if (this->doShoot) shoot();
	if (this->raiseAngle) increaseAngle();
	if (this->lowerAngle) decreaseAngle();
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
	b2Vec2 vel = m_body->GetLinearVelocity();
	float scaling = 0.7;
	/*
	float scaling = abs(vel.x);
	if (scaling < 0.5)
		scaling = 0.5;
	if (scaling > 0.5)
		scaling = 0.5;
	*/

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

/**
Sets duck's jump state depending
on contacts duck has.
*/
void Duck::setJumpingState()
{
	if (m_body->GetContactList() != 0){
		jumping = 0;
	}
	else{
		jumping = 1;
	}
}

/**
Returns correct texture depending
on value of "jumping" and "direction"
variables.
*/
GLuint Duck::getTextureToBind()
{
	if (jumping == 0){
		if (direction == 1){
			return m_tex[0];
		}
		if (direction == 0){
			return m_tex[1];
		}
	}
	if (jumping == 1){
		if (direction == 1){
			return m_tex[2];
		}
		if (direction == 0){
			return m_tex[3];
		}
	}
}

void Duck::increaseAngle()
{
	shootingAngle = shootingAngle + 5;
}

void Duck::decreaseAngle()
{
	shootingAngle = shootingAngle - 5;
}

