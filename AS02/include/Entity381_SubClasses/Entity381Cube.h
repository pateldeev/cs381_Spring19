/*
 -----------------------------------------------------------------------------
 Filename: Entity381Cube.h
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains declaration of Entity381Cube class
 */

#ifndef ENTITY381CUBE_H_
#define ENTITY381CUBE_H_

#include "Entity381.h"

class Entity381Cube: public Entity381 {

public:
	Entity381Cube(unsigned int id, const std::string &name, Ogre::SceneManager *scene_manager, const Ogre::Vector3 &position = Ogre::Vector3(0.f),
		const Ogre::Vector3 &scale = Ogre::Vector3(1.f), const Ogre::Vector3 &velocity = Ogre::Vector3(0.f));
	virtual ~Entity381Cube(void);

	//Entity381Cube is not meant to be copied or moved - for simplicity
	Entity381Cube(const Entity381Cube&) = delete;
	Entity381Cube(Entity381Cube&&) = delete;
	Entity381Cube& operator=(const Entity381Cube&) = delete;
	Entity381Cube& operator=(Entity381Cube&&) = delete;
};

#endif /* ENTITY381CUBE_H_ */
