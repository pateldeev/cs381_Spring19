/*
 -----------------------------------------------------------------------------
 Filename: Entity381Alien.h
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains declaration of Entity381Alien class
 */

#ifndef ENTITY381ALIEN_H_
#define ENTITY381ALIEN_H_

#include "Entity381.h"

class Entity381Alien: public Entity381 {

public:
	Entity381Alien(unsigned int id, const std::string &name, Ogre::SceneManager *scene_manager, const Ogre::Vector3 &position = Ogre::Vector3(0.f),
		const Ogre::Vector3 &scale = Ogre::Vector3(1.f));
	virtual ~Entity381Alien(void);

	//Entity381Alien is not meant to be copied or moved - for simplicity
	Entity381Alien(const Entity381Alien&) = delete;
	Entity381Alien(Entity381Alien&&) = delete;
	Entity381Alien& operator=(const Entity381Alien&) = delete;
	Entity381Alien& operator=(Entity381Alien&&) = delete;
};

#endif /* ENTITY381ALIEN_H_ */
