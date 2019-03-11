#ifndef ENTITY381ALIEN_H_
#define ENTITY381ALIEN_H_

#include "Entity381_SubClasses/Entity381Flying.h"

class Entity381Alien: public Entity381Flying {

public:
	Entity381Alien(unsigned int id, const std::string &name, Ogre::SceneManager *scene_manager, const Ogre::Vector3 &position = Ogre::Vector3(0.f),
		const Ogre::Vector3 &scale = Ogre::Vector3(1.f));
	virtual ~Entity381Alien(void);
};

#endif
