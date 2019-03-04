/*
 -----------------------------------------------------------------------------
 Filename: Entity381Sphere.cpp
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains implementation of Entity381Sphere class
 */

#include "Entity381_SubClasses/Entity381Sphere.h"

Entity381Sphere::Entity381Sphere(unsigned int id, const std::string &name, Ogre::SceneManager *scene_manager, const Ogre::Vector3 &position,
	const Ogre::Vector3 &scale, const Ogre::Vector3 &velocity) :
	Entity381(id, name, scene_manager, position, scale, velocity) {

	m_entity = scene_manager->createEntity("sphere.mesh");
	m_scene_node->attachObject(m_entity);

	//add aspects
	m_aspects.push_back(new AspectPhysics(this));
	m_aspects.push_back(new AspectRenderable(this));
	m_aspects.push_back(new AspectRotator(this, (std::rand() / double(RAND_MAX)) * 2));
}

Entity381Sphere::~Entity381Sphere(void) {

}

