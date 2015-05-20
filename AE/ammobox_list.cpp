#include <algorithm>
#include "ammobox_list.h"

ammobox_list* ammobox_list::m_instance = 0;

/**
Adds an item to the list (only once).
*/
void ammobox_list::push_back_unique(Ammobox *p)
{
	if (std::find(begin(), end(), p) == end())
		push_back(p);
}