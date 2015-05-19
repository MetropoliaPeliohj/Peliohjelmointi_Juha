#ifndef _IPHYSABLE_H_
#define _IPHYSABLE_H_

#include <Box2D/Box2D.h>


/**
	Base class for dynamic objects that are
	under physics simulation.
*/
class IPhysable
{

public:

	IPhysable()			{}
	virtual ~IPhysable() {}

	b2Body* get_body()	{ return m_body; }

protected:

	// Body knows position and rotation.
	b2Body* m_body;

};

#endif // _IPHYSABLE_H_
