/*
 -----------------------------------------------------------------------------
 Filename: AspectRotator.h
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains declaration of AspectRotator class
 */

#ifndef ASPECTROTATOR_H_
#define ASPECTROTATOR_H_

#include "Aspect.h"

class AspectRotator: public Aspect {

public:
	AspectRotator(Entity381 *parent, float rotation_speed = 0.4);
	virtual ~AspectRotator(void);

	//AspectRotator is not meant to be copied or moved - for simplicity
	AspectRotator(const AspectRotator&) = delete;
	AspectRotator(AspectRotator&&) = delete;
	AspectRotator& operator=(const AspectRotator&) = delete;
	AspectRotator& operator=(AspectRotator&&) = delete;

	virtual void Tick(float dt) override final;

private:
	float m_rotation_speed;
};

#endif /* ASPECTROTATOR_H_ */
