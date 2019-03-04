/*
 -----------------------------------------------------------------------------
 Filename: Entity381Carrier.h
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains declaration of Entity381Carrier class
 */

#ifndef ENTITY381CARRIER_H_
#define ENTITY381CARRIER_H_

#include "Entity381.h"

class Entity381Carrier: public Entity381 {

public:
	Entity381Carrier(unsigned int id, const std::string &name, Ogre::SceneManager *scene_manager, const Ogre::Vector3 &position = Ogre::Vector3(0.f),
		const Ogre::Vector3 &scale = Ogre::Vector3(1.f));
	virtual ~Entity381Carrier(void);

	//Entity381Carrier is not meant to be copied or moved - for simplicity
	Entity381Carrier(const Entity381Carrier&) = delete;
	Entity381Carrier(Entity381Carrier&&) = delete;
	Entity381Carrier& operator=(const Entity381Carrier&) = delete;
	Entity381Carrier& operator=(Entity381Carrier&&) = delete;
};

#endif /* ENTITY381CARRIER_H */
