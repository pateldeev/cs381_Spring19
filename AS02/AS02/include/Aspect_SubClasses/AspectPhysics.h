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
};

#endif /* ASPECTPHYSICS_H_ */
