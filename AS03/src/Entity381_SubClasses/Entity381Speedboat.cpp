/*
 -----------------------------------------------------------------------------
 Filename: Entity381Speedboat.cpp
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains implementation of Entity381Speedboat class
 */

#include "Entity381_SubClasses/Entity381Speedboat.h"

Entity381Speedboat::Entity381Speedboat(unsigned int id, const std::string &name, Ogre::SceneManager *scene_manager, const Ogre::Vector3 &position,
	const Ogre::Vector3 &scale) :
	Entity381(id, name, "cigarette.mesh", scene_manager, position, scale) {

	//defining characteristics of boat
	m_speed_max = 150.f;
	m_acceleration = 100.f;
	m_turning_rate = 30.f;

	//add aspects
	m_aspects.push_back(new AspectPhysics(this));
	m_aspects.push_back(new AspectRenderable(this));
}

Entity381Speedboat::~Entity381Speedboat(void) {

}

