/*
 -----------------------------------------------------------------------------
 Filename: Entity381Destroyer.h
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains declaration of Entity381Destroyer class
 */

#ifndef ENTITY381DESTROYER_H_
#define ENTITY381DESTROYER_H_

#include "Entity381.h"

class Entity381Destroyer: public Entity381 {

public:
	Entity381Destroyer(unsigned int id, const std::string &name, Ogre::SceneManager *scene_manager, const Ogre::Vector3 &position = Ogre::Vector3(0.f),
		const Ogre::Vector3 &scale = Ogre::Vector3(1.f));
	virtual ~Entity381Destroyer(void);

	//Entity381Destroyer is not meant to be copied or moved - for simplicity
	Entity381Destroyer(const Entity381Destroyer&) = delete;
	Entity381Destroyer(Entity381Destroyer&&) = delete;
	Entity381Destroyer& operator=(const Entity381Destroyer&) = delete;
	Entity381Destroyer& operator=(Entity381Destroyer&&) = delete;
};

#endif /* ENTITY381DESTROYER_H_ */
