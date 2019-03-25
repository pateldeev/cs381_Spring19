#include <Aspect.h>
#include <Entity381.h>  //Aspect includes Entity381.h

Renderable::Renderable(Entity381* ent) :
	Aspect(ent) {

}

Renderable::~Renderable() {

}

void Renderable::Tick(float dt) {
	//do something;
	entity->sceneNode->setPosition(entity->position); //now ogre should render the sceneNode at the new position...
	entity->sceneNode->resetOrientation(); // yaw is relative to 0
	entity->sceneNode->yaw(Ogre::Degree(-entity->heading));
}
