#include <algorithm>
#include <list>
#include "ae.h"
#include "bullet.h"
#include "deletion_list.h"
#include "duck.h"
#include "log.h"
#include "render_list.h"
#include "collision.h"
#include "ai_list.h"
#include "IHealthable.h"
#include "Character_list.h"
#include "ICharacter.h"
#include "ammobox.h"
#include "ammobox_list.h"
#include "render_list.h"

Contact_Listener* Contact_Listener::m_instance = 0;
boolean Contact_Listener::contactState;

/*
	Collision (begin).
*/
void Contact_Listener::BeginContact(b2Contact *contact)
{
	contactState = true;
	Log::log(LOG_INFO, "Begin contact");
	b2Body *body_a = contact->GetFixtureA()->GetBody();
	b2Body *body_b = contact->GetFixtureB()->GetBody();

	this->checkIfBulletHitSomeone(body_a, body_b);

	/*
	b2Body *body_ammo1 = Ammobox::bodies.front();
	b2Body *body_ammo2 = Ammobox::bodies.front();
	b2Body *body_ammo3 = Ammobox::bodies.front();
	Ammobox* box1 = Ammobox::ammoboxes.front();
	Ammobox* box2 = Ammobox::ammoboxes.front();
	Ammobox* box3 = Ammobox::ammoboxes.front();

	// Check if the duck has collected a box.
	if (body_ammo1 == body_d){
		box1->kill();
	}
	if (body_ammo2 == body_d){
		box2->kill();
	}
	if (body_ammo3 == body_d){
		box3->kill();
	}
	*/
	// Delete bullets from rendering and physics.
	if (body_a->IsBullet())
	{
		Render_List::get()->remove((Bullet*)(body_a->GetUserData()));
		Deletion_List::get()->push_back_unique((Bullet*)(body_a->GetUserData()));
	}
	if (body_b->IsBullet())
	{
		Render_List::get()->remove((Bullet*)(body_b->GetUserData()));
		Deletion_List::get()->push_back_unique((Bullet*)(body_b->GetUserData()));
	}
}


/**
	Collision (end).
*/
void Contact_Listener::EndContact(b2Contact *contact)
{
	Log::log(LOG_INFO, "End contact");
}

void Contact_Listener::checkIfBulletHitSomeone(b2Body *body_a, b2Body *body_b)
{
	// Check if the someone bites a bullet.
	if (body_a->IsBullet() || body_b->IsBullet())
	{
		for (Character_list::iterator i = Character_list::get()->begin(); i != Character_list::get()->end(); i++)
		{
			b2Body *body = (*i)->get_body();
			if (body_a == body || body_b == body)
			{
 				(*i)->damageReceived(BULLET_DAMAGE);
			}
		}
	}

	b2Body *body_d = Duck::get_duck()->get_body();
	for (ammobox_list::iterator i = ammobox_list::get()->begin(); i != ammobox_list::get()->end(); i++)
	{
		b2Body *body = (*i)->get_body();
		if (body_d == body)
		{
			Deletion_List::get()->push_back_unique((*i));
		}
	}
}
