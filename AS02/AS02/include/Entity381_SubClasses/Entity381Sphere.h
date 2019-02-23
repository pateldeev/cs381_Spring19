/*
 -----------------------------------------------------------------------------
 Filename:    Entity381Sphere.h
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains declaration of Entity381Cube class
 */

#ifndef ENTITY381SPHERE_H_
#define ENTITY381SPHERE_H_

#include "Entity381.h"

class Entity381Sphere: public Entity381 {

public:
	Entity381Sphere(unsigned int id, const std::string &name, Ogre::SceneManager *scene_manager, const Ogre::Vector3 &position = Ogre::Vector3(0.f),
		const Ogre::Vector3 &scale = Ogre::Vector3(1.f), const Ogre::Vector3 &velocity = Ogre::Vector3(0.f));
	virtual ~Entity381Sphere(void);

	//Entity381Sphere is not meant to be copied or moved - for simplicity
	Entity381Sphere(const Entity381Sphere&) = delete;
	Entity381Sphere(Entity381Sphere&&) = delete;
	Entity381Sphere& operator=(const Entity381Sphere&) = delete;
	Entity381Sphere& operator=(Entity381Sphere&&) = delete;
};

#endif /* ENTITY381SPHERE_H_ */
