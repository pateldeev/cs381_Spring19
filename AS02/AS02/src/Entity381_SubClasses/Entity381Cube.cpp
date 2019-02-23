/*
 -----------------------------------------------------------------------------
 Filename: Entity381Cube.cpp
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains implementation of Entity381Cube class
 */

#include "Entity381_SubClasses/Entity381Cube.h"

Entity381Cube::Entity381Cube(unsigned int id, const std::string &name, Ogre::SceneManager *scene_manager, const Ogre::Vector3 &position,
	const Ogre::Vector3 &scale, const Ogre::Vector3 &velocity) :
	Entity381(id, name, scene_manager, position, scale, velocity) {

	m_entity = scene_manager->createEntity("cube.mesh");
	m_scene_node->attachObject(m_entity);

	//add aspects
	m_aspects.push_back(new AspectPhysics(this));
	m_aspects.push_back(new AspectRenderable(this));
	m_aspects.push_back(new AspectRotator(this, (std::rand() / double(RAND_MAX)) * 2));
}

Entity381Cube::~Entity381Cube(void) {

}

