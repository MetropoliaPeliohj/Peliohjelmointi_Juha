#ifndef _AMMOBOX_LIST_H_
#define _AMMOBOX_LIST_H_


#include <list>
#include "Ammobox.h"



class ammobox_list : public std::list<Ammobox*>
{
public:

	// Instance access.
	static ammobox_list* get()
	{
		if (!ammobox_list::m_instance)
			ammobox_list::m_instance = new ammobox_list();
		return ammobox_list::m_instance;
	}

	void push_back_unique(Ammobox*);

private:

	// (Singleton) instance.
	static ammobox_list* m_instance;

	ammobox_list() {}
	~ammobox_list() {}
};


#endif // _AMMOBOX_LIST_H_