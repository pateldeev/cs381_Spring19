#include <Aspect.h>
#include <Entity381.h>  //Aspect includes Entity381.h

Renderable::Renderable(Entity381* ent) :
	Aspect(ent) {

}

Renderable::~Renderable() {

}

void Renderable::Tick(float dt) {
	entity->sceneNode->setPosition(entity->position);
	entity->sceneNode->resetOrientation(); // yaw is relative to 0
	entity->sceneNode->yaw(Ogre::Degree(-entity->heading));

	if (entity->roll < entity->desiredRoll - 0.25)
		entity->roll += 0.2;
	else if (entity->roll > entity->desiredRoll + 0.25)
		entity->roll -= 0.2;
	entity->sceneNode->roll(Ogre::Degree(-entity->roll));
}
