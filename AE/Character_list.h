#ifndef _CHARACTER_LIST_H_
#define _CHARACTER_LIST_H_


#include <list>
#include "ICharacter.h"


class Character_list : public std::list<ICharacter*>
{
public:

	// Instance access.
	static Character_list* get()
	{
		if (!Character_list::m_instance)
			Character_list::m_instance = new Character_list();
		return Character_list::m_instance;
	}

	void push_back_unique(ICharacter*);

private:

	// (Singleton) instance.
	static Character_list* m_instance;

	Character_list() {}
	~Character_list() {}
};



#endif // _CHARACTER_LIST_H_