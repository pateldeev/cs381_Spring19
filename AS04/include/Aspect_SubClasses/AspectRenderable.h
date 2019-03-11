#ifndef ASPECTRENDERABLE_H_
#define ASPECTRENDERABLE_H_

#include "Aspect.h"

class AspectRenderable: public Aspect {

public:
	AspectRenderable(Entity381 *parent);
	virtual ~AspectRenderable(void);

public:
	virtual void Tick(float dt) override final;
};

#endif
