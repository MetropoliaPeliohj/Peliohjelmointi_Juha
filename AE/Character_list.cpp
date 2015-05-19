#include <algorithm>
#include "Character_list.h"

Character_list* Character_list::m_instance = 0;


/**
Adds an item to the list (only once).
*/
void Character_list::push_back_unique(ICharacter *p)
{
	if (std::find(begin(), end(), p) == end())
		push_back(p);
}
