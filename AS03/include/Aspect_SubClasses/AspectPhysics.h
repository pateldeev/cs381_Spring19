/*
 -----------------------------------------------------------------------------
 Filename: AspectPhysics.h
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains declaration of AspectPhysics class
 */

#ifndef ASPECTPHYSICS_H_
#define ASPECTPHYSICS_H_

#include "Aspect.h"

#include <OgreVector3.h>

class AspectPhysics: public Aspect {

public:
	AspectPhysics(Entity381 *parent);
	virtual ~AspectPhysics(void);

	//AspectPhysics is not meant to be copied or moved - for simplicity
	AspectPhysics(const AspectPhysics&) = delete;
	AspectPhysics(AspectPhysics&&) = delete;
	AspectPhysics& operator=(const AspectPhysics&) = delete;
	AspectPhysics& operator=(AspectPhysics&&) = delete;

	virtual void Tick(float dt) override final;

private:
	float getNewHeading(float current, float desired, float max_change, float acceptable_error = 1.f);
	float getNewSpeed(float current, float desired, float max_change, float acceptable_error = 1.f);

	Ogre::Vector3 getVelocityInDirectionOfHeading(float heading, float speed);
};

#endif /* ASPECTPHYSICS_H_ */
