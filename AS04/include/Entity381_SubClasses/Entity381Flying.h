#ifndef ENTITY381FLYING_H_
#define ENTITY381FLYING_H_

#include "Entity381.h"

class Entity381Flying: public Entity381 {

public:
	virtual ~Entity381Flying(void);

public:
	void ChangeDesiredHeight(float amount);
	void TickHeight(float dt);

protected:
	Entity381Flying(unsigned int id, const std::string &name, const std::string &mesh_file, Ogre::SceneManager *scene_manager,
		const Ogre::Vector3 &position = Ogre::Vector3(0.f), const Ogre::Vector3 &scale = Ogre::Vector3(1.f)); //only meant to be called by subclasses

protected:
	float m_vertical_acceleration;

private:
	float m_height;
	float m_height_desired;

};

#include "Entity381_SubClasses/Entity381Alien.h"

#endif
