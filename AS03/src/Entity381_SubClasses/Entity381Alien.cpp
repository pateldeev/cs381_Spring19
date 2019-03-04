/*
 -----------------------------------------------------------------------------
 Filename: Entity381Alien.cpp
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains implementation of Entity381Alien class
 */

#include "Entity381_SubClasses/Entity381Alien.h"

Entity381Alien::Entity381Alien(unsigned int id, const std::string &name, Ogre::SceneManager *scene_manager, const Ogre::Vector3 &position,
	const Ogre::Vector3 &scale) :
	Entity381(id, name, "alienship.mesh", scene_manager, position, scale) {

	//defining characteristics of boat
	m_speed_max = 250.f;
	m_acceleration = 200.f;
	m_turning_rate = 50.f;

	//add aspects
	m_aspects.push_back(new AspectPhysics(this));
	m_aspects.push_back(new AspectRenderable(this));
}

Entity381Alien::~Entity381Alien(void) {

}

