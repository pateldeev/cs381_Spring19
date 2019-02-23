/*
 -----------------------------------------------------------------------------
 Filename: Aspect.h
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains declaration of Aspect class
 */

#ifndef ASPECT_H_
#define ASPECT_H_

class Entity381;
//necessary forward declaration

class Aspect {

public:
	virtual ~Aspect(void);

	//Aspect is not meant to be copied or moved - for simplicity
	Aspect(const Aspect&) = delete;
	Aspect(Aspect&&) = delete;
	Aspect& operator=(const Aspect&) = delete;
	Aspect& operator=(Aspect&&) = delete;

	virtual void Tick(float dt) = 0; //implemented by various subclasses

protected:
	//only meant to be created by subclasses
	Aspect(Entity381 *parent);

protected:
	Entity381 *m_parent_entity;

};

//for dealing with various subclasses
enum AspectType {
	PHYSICS, RENDERABLE, ROTATOR
};

#include "Aspect_SubClasses/AspectPhysics.h"
#include "Aspect_SubClasses/AspectRenderable.h"
#include "Aspect_SubClasses/AspectRotator.h"

#endif /* ASPECT_H_ */
