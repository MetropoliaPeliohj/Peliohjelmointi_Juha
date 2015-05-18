#ifndef _IAI_CHARACTER_H_
#define _IAI_CHARACTER_H_

/**
	Base class for AI controlled objects.
*/
class IAI_Character
{
public:
	IAI_Character()			{}
	virtual ~IAI_Character()	{}

	virtual void run_ai() = 0;
};

#endif // _IAI_CHARACTER_H_
