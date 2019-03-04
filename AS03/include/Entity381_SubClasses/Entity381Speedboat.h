/*
 -----------------------------------------------------------------------------
 Filename: Entity381Speedboat.h
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains declaration of Entity381Speedboat class
 */

#ifndef ENTITY381SPEEDBOAT_H_
#define ENTITY381SPEEDBOAT_H_

#include "Entity381.h"

class Entity381Speedboat: public Entity381 {

public:
	Entity381Speedboat(unsigned int id, const std::string &name, Ogre::SceneManager *scene_manager,
		const Ogre::Vector3 &position = Ogre::Vector3(0.f), const Ogre::Vector3 &scale = Ogre::Vector3(1.f));
	virtual ~Entity381Speedboat(void);

	//Entity381Speedboat is not meant to be copied or moved - for simplicity
	Entity381Speedboat(const Entity381Speedboat&) = delete;
	Entity381Speedboat(Entity381Speedboat&&) = delete;
	Entity381Speedboat& operator=(const Entity381Speedboat&) = delete;
	Entity381Speedboat& operator=(Entity381Speedboat&&) = delete;
};

#endif /* ENTITY381SPEEDBOAT_H_ */
