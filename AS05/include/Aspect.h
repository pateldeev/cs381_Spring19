#ifndef __Aspect_h_
#define __Aspect_h_

#include <OGRE/OgreVector3.h>

//Forward declaration of the Entity381 class
class Entity381;

class Aspect {
public:
	Aspect(Entity381* ent);
	virtual ~Aspect();

	Entity381* entity;

	virtual void Tick(float dt);

protected:

};

class Renderable: Aspect {
public:
	Renderable(Entity381* ent);
	~Renderable();

	void Tick(float dt);
};

class Physics2D: Aspect {
public:
	Physics2D(Entity381 *ent);
	~Physics2D();

	void Tick(float dt);
};

class Physics3D: Aspect {
public:
	Physics3D(Entity381 *ent);
	~Physics3D();

	void Tick(float dt);
};

#endif // #ifndef __Aspect_h_
