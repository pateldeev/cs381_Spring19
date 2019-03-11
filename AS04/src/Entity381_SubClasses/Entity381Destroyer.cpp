#include "Entity381_SubClasses/Entity381Destroyer.h"

Entity381Destroyer::Entity381Destroyer(unsigned int id, const std::string &name, Ogre::SceneManager *scene_manager, const Ogre::Vector3 &position,
	const Ogre::Vector3 &scale) :
	Entity381(id, name, "ddg51.mesh", scene_manager, position, scale) {

	//defining characteristics of boat
	m_speed_max = 250.f;
	m_acceleration = 40.f;
	m_turning_rate = 22.f;

	//add aspects
	m_aspects.push_back(new AspectPhysics(this));
	m_aspects.push_back(new AspectRenderable(this));
}

Entity381Destroyer::~Entity381Destroyer(void) {

}
