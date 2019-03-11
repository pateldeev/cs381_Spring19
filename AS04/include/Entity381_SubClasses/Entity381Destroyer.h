#ifndef ENTITY381DESTROYER_H_
#define ENTITY381DESTROYER_H_

#include "Entity381.h"

class Entity381Destroyer: public Entity381 {

public:
	Entity381Destroyer(unsigned int id, const std::string &name, Ogre::SceneManager *scene_manager, const Ogre::Vector3 &position = Ogre::Vector3(0.f),
		const Ogre::Vector3 &scale = Ogre::Vector3(1.f));
	virtual ~Entity381Destroyer(void);
};

#endif
