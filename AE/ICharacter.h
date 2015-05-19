#ifndef _ICHARACTER_H_
#define _ICHARACTER_H_

#include "IPhysable.h"
#include "IShootable.h"
#include "IHealthable.h"



class ICharacter : public IPhysable, public IShootable, public IHealthable
{

public:
	ICharacter() {}
	virtual ~ICharacter() {}

};



#endif // _ICHARACTER_H_



