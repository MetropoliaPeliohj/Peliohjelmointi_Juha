#ifndef _AMMO_LIST_H_
#define _AMMO_LIST_H_

#include <list>
#include "Irenderable.h"
#include "ammobox.h"

/**
For keeping track of and for rendering of
all the renderable items. Singleton.
*/
class Ammo_List : public std::list<Ammobox*>
{
public:

	// Instance access.
	static Ammo_List* get()
	{
		if (!Ammo_List::m_instance)
			Ammo_List::m_instance = new Ammo_List();
		return Ammo_List::m_instance;
	}

private:

	Ammo_List()	{}
	~Ammo_List()	{}

	// (Singleton) instance;
	static Ammo_List* m_instance;
};

#endif // _AMMO_LIST_H_
