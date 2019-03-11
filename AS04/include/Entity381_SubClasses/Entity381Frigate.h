#ifndef ENTITY381FRIGATE_H_
#define ENTITY381FRIGATE_H_

#include "Entity381.h"

class Entity381Frigate: public Entity381 {

public:
	Entity381Frigate(unsigned int id, const std::string &name, Ogre::SceneManager *scene_manager, const Ogre::Vector3 &position = Ogre::Vector3(0.f),
		const Ogre::Vector3 &scale = Ogre::Vector3(1.f));
	virtual ~Entity381Frigate(void);
};

#endif
