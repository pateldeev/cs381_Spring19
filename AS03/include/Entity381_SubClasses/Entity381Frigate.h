/*
 -----------------------------------------------------------------------------
 Filename: Entity381Frigate.h
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains declaration of Entity381Frigate class
 */

#ifndef ENTITY381FRIGATE_H_
#define ENTITY381FRIGATE_H_

#include "Entity381.h"

class Entity381Frigate: public Entity381 {

public:
	Entity381Frigate(unsigned int id, const std::string &name, Ogre::SceneManager *scene_manager, const Ogre::Vector3 &position = Ogre::Vector3(0.f),
		const Ogre::Vector3 &scale = Ogre::Vector3(1.f));
	virtual ~Entity381Frigate(void);

	//Entity381Frigate is not meant to be copied or moved - for simplicity
	Entity381Frigate(const Entity381Frigate&) = delete;
	Entity381Frigate(Entity381Frigate&&) = delete;
	Entity381Frigate& operator=(const Entity381Frigate&) = delete;
	Entity381Frigate& operator=(Entity381Frigate&&) = delete;
};

#endif /* ENTITY381FRIGATE_H_ */
