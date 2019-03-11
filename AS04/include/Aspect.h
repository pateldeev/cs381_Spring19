#ifndef ASPECT_H_
#define ASPECT_H_

//necessary forward declaration
class Entity381;

class Aspect {

public:
	virtual ~Aspect(void);

public:
	virtual void Tick(float dt) = 0; //implemented by various subclasses

protected:
	Aspect(Entity381 *parent); //only meant to be created by subclasses
protected:
	Entity381 *m_parent_entity;

};

//for dealing with various subclasses
enum AspectType {
	PHYSICS, RENDERABLE
};

#include "Aspect_SubClasses/AspectPhysics.h"
#include "Aspect_SubClasses/AspectRenderable.h"

#endif
