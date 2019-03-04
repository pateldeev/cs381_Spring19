/*
 -----------------------------------------------------------------------------
 Filename: Entity381.h
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains declaration of Entity381 class
 */

#ifndef ENTITY381_H_
#define ENTITY381_H_

#include <OgreEntity.h>
#include <OgreSceneManager.h>

#include "Aspect.h"

#include <vector>

class Entity381 {

public:
	virtual ~Entity381(void);

	//Entity381 is not meant to be copied or moved - for simplicity
	Entity381(const Entity381&) = delete;
	Entity381(Entity381&&) = delete;
	Entity381& operator=(const Entity381&) = delete;
	Entity381& operator=(Entity381&&) = delete;

	void showBoundingBox(bool show);

	void setVelocity(const Ogre::Vector3 &velocity, bool accumulate = true);

	void Tick(float dt);

protected:
	//only meant to be created by subclasses
	Entity381(unsigned int id, const std::string &name, Ogre::SceneManager *scene_manager, const Ogre::Vector3 &position = Ogre::Vector3(0.f),
		const Ogre::Vector3 &scale = Ogre::Vector3(1.f), const Ogre::Vector3 &velocity = Ogre::Vector3(0.f));

protected:
	unsigned int m_id;
	std::string m_name;

	Ogre::Vector3 m_position;
	Ogre::Vector3 m_velocity;

	Ogre::SceneNode *m_scene_node;
	Ogre::Entity *m_entity;

	std::vector<Aspect*> m_aspects;

	friend class AspectPhysics;
	friend class AspectRenderable;
	friend class AspectRotator;
};

//for dealing with various subclasses
enum EntityType {
	CUBE, SPHERE
};

#include "Entity381_SubClasses/Entity381Cube.h"
#include "Entity381_SubClasses/Entity381Sphere.h"

//---------------------------------------------------------------------------

#endif  /* ENTITY381_H_ */

//---------------------------------------------------------------------------
