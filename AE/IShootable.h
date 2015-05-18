#ifndef _ISHOOTABLE_H_
#define _ISHOOTABLE_H_


/**
	Virtual class for all objects that can shoot.
*/
class IShootable
{
public:
	IShootable()			{}
	virtual ~IShootable() {}

	void try_shoot(int, int, float, float, unsigned int);

private:
	long lastTimeShotTimestamp;
};

#endif // _ISHOOTABLE_H_