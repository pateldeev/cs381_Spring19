#ifndef ASPECTPHYSICS_H_
#define ASPECTPHYSICS_H_

#include "Aspect.h"

#include <OgreVector3.h>

class AspectPhysics: public Aspect {

public:
	AspectPhysics(Entity381 *parent);
	virtual ~AspectPhysics(void);

public:
	virtual void Tick(float dt) override final;

private:
	float GetNewHeading(float current, float desired, float max_change, float acceptable_error = 1.f);
	float GetNewSpeed(float current, float desired, float max_change, float acceptable_error = 1.f);

	Ogre::Vector3 GetVelocityInDirectionOfHeading(float heading, float speed);
};

#endif
