/*
 -----------------------------------------------------------------------------
 Filename: AspectRenderable.h
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains declaration of AspectRenderable class
 */

#ifndef ASPECTRENDERABLE_H_
#define ASPECTRENDERABLE_H_

#include "Aspect.h"

class AspectRenderable: public Aspect {

public:
	AspectRenderable(Entity381 *parent);
	virtual ~AspectRenderable(void);

	//AspectRenderable is not meant to be copied or moved - for simplicity
	AspectRenderable(const AspectRenderable&) = delete;
	AspectRenderable(AspectRenderable&&) = delete;
	AspectRenderable& operator=(const AspectRenderable&) = delete;
	AspectRenderable& operator=(AspectRenderable&&) = delete;

	virtual void Tick(float dt) override final;
};

#endif /* ASPECTRENDERABLE_H_ */
