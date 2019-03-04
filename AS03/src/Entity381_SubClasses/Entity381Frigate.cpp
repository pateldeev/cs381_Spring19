/*
 -----------------------------------------------------------------------------
 Filename: Entity381Frigate.cpp
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains implementation of Entity381Frigate class
 */

#include "Entity381_SubClasses/Entity381Frigate.h"

Entity381Frigate::Entity381Frigate(unsigned int id, const std::string &name, Ogre::SceneManager *scene_manager, const Ogre::Vector3 &position,
	const Ogre::Vector3 &scale) :
	Entity381(id, name, "sleek.mesh", scene_manager, position, scale) {

	//defining characteristics of boat
	m_speed_max = 220.f;
	m_acceleration = 35.f;
	m_turning_rate = 18.f;

	//add aspects
	m_aspects.push_back(new AspectPhysics(this));
	m_aspects.push_back(new AspectRenderable(this));
}

Entity381Frigate::~Entity381Frigate(void) {

}

