#include "Entity381_SubClasses/Entity381Carrier.h"

Entity381Carrier::Entity381Carrier(unsigned int id, const std::string &name, Ogre::SceneManager *scene_manager, const Ogre::Vector3 &position,
	const Ogre::Vector3 &scale) :
	Entity381(id, name, "cvn68.mesh", scene_manager, position, scale) {

	//defining characteristics of boat
	m_speed_max = 350.f;
	m_acceleration = 20.f;
	m_turning_rate = 8.f;

	//add aspects
	m_aspects.push_back(new AspectPhysics(this));
	m_aspects.push_back(new AspectRenderable(this));
}

Entity381Carrier::~Entity381Carrier(void) {

}
