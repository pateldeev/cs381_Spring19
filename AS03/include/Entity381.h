/*
 -----------------------------------------------------------------------------
 Filename: Entity381.h
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains declaration of Entity381 class
 */

#ifndef ENTITY381_H_
#define ENTITY381_H_

#include <OgreEntity.h>
#include <OgreSceneManager.h>

#include "Aspect.h"

#include <vector>

class Entity381 {

public:
	virtual ~Entity381(void);

	//Entity381 is not meant to be copied or moved - for simplicity
	Entity381(const Entity381&) = delete;
	Entity381(Entity381&&) = delete;
	Entity381& operator=(const Entity381&) = delete;
	Entity381& operator=(Entity381&&) = delete;

	void showBoundingBox(bool show);
	std::string getName(void) const;

	void changeDesiredSpeed(float amount);
	void changeDesiredHeading(float amount);

	std::pair<float, float> getDesiredHeadingAndSpeed(void) const;

	void Tick(float dt);

protected:
	//only meant to be created by subclasses
	Entity381(unsigned int id, const std::string &entity_name, const std::string &mesh_file, Ogre::SceneManager *scene_manager,
		const Ogre::Vector3 &position = Ogre::Vector3(0.f), const Ogre::Vector3 &scale = Ogre::Vector3(1.f));

protected:
	unsigned int m_id;
	std::string m_name;
	std::string m_mesh_file;

	float m_speed;
	float m_speed_max;
	float m_speed_desired;
	float m_heading; //in degree [0,360)
	float m_heading_desired;
	float m_acceleration;
	float m_turning_rate;

	Ogre::Vector3 m_position;
	Ogre::Vector3 m_velocity;

	Ogre::SceneNode *m_scene_node;
	Ogre::Entity *m_entity;

	std::vector<Aspect*> m_aspects;

	friend class AspectPhysics;
	friend class AspectRenderable;
};

//for dealing with various subclasses
enum EntityType {
	DESTROYER, CARRIER, SPEEDBOAT, FRIGATE, ALIEN
};

#include "Entity381_SubClasses/Entity381Destroyer.h"
#include "Entity381_SubClasses/Entity381Carrier.h"
#include "Entity381_SubClasses/Entity381Speedboat.h"
#include "Entity381_SubClasses/Entity381Frigate.h"
#include "Entity381_SubClasses/Entity381Alien.h"

//---------------------------------------------------------------------------

#endif  /* ENTITY381_H_ */

//---------------------------------------------------------------------------
