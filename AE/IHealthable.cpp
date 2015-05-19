
#include "IHealthable.h"
#include "Log.h"


void IHealthable::damageReceived(unsigned char damage)
{
	this->health -= damage;
	if (this->health <= 0)
	{
		m_is_alive = false;
	}
	Log::log(0, "*** Someone got hit ***");
}

IHealthable::IHealthable()
{
}


IHealthable::~IHealthable()
{
}
