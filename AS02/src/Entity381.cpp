/*
 -----------------------------------------------------------------------------
 Filename: Entity381.cpp
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains implementation of Entity381 class
 */

#include "Entity381.h"

Entity381::Entity381(unsigned int id, const std::string &name, Ogre::SceneManager *scene_manager, const Ogre::Vector3 &position,
	const Ogre::Vector3 &scale, const Ogre::Vector3 &velocity) :
	m_id(id), m_name(name), m_position(position), m_velocity(velocity), m_scene_node(nullptr), m_entity(nullptr) {

	m_scene_node = scene_manager->getRootSceneNode()->createChildSceneNode(m_name, position);
	m_scene_node->scale(scale);
}

Entity381::~Entity381(void) {
	for (Aspect *a : m_aspects)
		delete a;
}

void Entity381::showBoundingBox(bool show) {
	m_scene_node->showBoundingBox(show);
}

void Entity381::setVelocity(const Ogre::Vector3 &velocity, bool accumulate) {
	if (accumulate)
		m_velocity += velocity;
	else
		m_velocity = velocity;
}

void Entity381::Tick(float dt) {
	for (Aspect *a : m_aspects)
		a->Tick(dt);
}

