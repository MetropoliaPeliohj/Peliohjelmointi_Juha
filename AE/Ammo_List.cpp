#include <list>
#include "ammo_list.h"

Ammo_List* Ammo_List::m_instance = 0;


/**
Runs AI on all the characters in the list.
*/
void Ammo_List::get_all_ammoboxes()
{
	for (Ammo_List::iterator i = begin(); i != end(); i++)
	{
		(*i)->run_ai();
	}
}