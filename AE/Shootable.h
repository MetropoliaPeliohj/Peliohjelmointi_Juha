#ifndef _SHOOTABLE_H_
#define _SHOOTABLE_H_


/**
	Virtual class for all objects that can shoot.
*/
class Shootable
{
public:
	Shootable()			{}
	virtual ~Shootable() {}

	void shoot(int, int, float, float, unsigned int);

private:
	long lastTimeShotTimestamp;
};

#endif // _SHOOTABLE_H_