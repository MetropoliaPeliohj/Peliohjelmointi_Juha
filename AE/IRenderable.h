#ifndef _IRENDERABLE_H_
#define _IRENDERABLE_H_

/**
	Base class for all objects that can be rendered onto screen.
*/
class IRenderable
{
public:
	IRenderable()			{}
	virtual ~IRenderable()	{}

	virtual void render() = 0;
};

#endif // _IRENDERABLE_H_
