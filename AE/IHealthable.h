#ifndef _IHEALTHABLE_H_
#define _IHEALTHABLE_H_




class IHealthable
{
public:
	void damageReceived(unsigned char);
	bool checkIfAlive() { return m_is_alive; }


	IHealthable();
	virtual ~IHealthable();

private:
	unsigned char health = 100;
	bool m_is_alive = true;
};



#endif // _IHEALTHABLE_H_