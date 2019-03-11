#ifndef ENTITY381_H_
#define ENTITY381_H_

#include <OgreEntity.h>
#include <OgreSceneManager.h>

#include "Aspect.h"

#include <vector>

//for dealing with various subclasses
enum EntityType {
	DESTROYER, CARRIER, SPEEDBOAT, FRIGATE, ALIEN
};

class Entity381 {

public:
	virtual ~Entity381(void);

public:
	void Tick(float dt);

	void ShowBoundingBox(bool show);
	std::string GetName(void) const;

	void ChangeDesiredSpeed(float amount);
	void ChangeDesiredHeading(float amount);
	bool ChangeDesiredHeight(float amount); //returns false if Entity is not flying

	std::pair<float, float> GetDesiredHeadingAndSpeed(void) const;
	std::pair<float, float> GetHeadingAndSpeed(void) const;
	Ogre::Vector3 GetEntityPosition(void) const;
	const Ogre::AxisAlignedBox& GetBoudingBox(void) const;

protected:
	Entity381(unsigned int id, const std::string &entity_name, const std::string &mesh_file, Ogre::SceneManager *scene_manager,
		const Ogre::Vector3 &position = Ogre::Vector3(0.f), const Ogre::Vector3 &scale = Ogre::Vector3(1.f)); //only meant to be created by subclasses

protected:
	float m_speed_max;
	float m_acceleration;
	float m_turning_rate;
	bool m_flying;
	Ogre::Vector3 m_position;
	Ogre::Vector3 m_velocity;

	std::vector<Aspect*> m_aspects;

private:
	unsigned int m_id;
	std::string m_name;
	std::string m_mesh_file;

	float m_speed;
	float m_speed_desired;
	float m_heading; //in degree [0,360)
	float m_heading_desired;

	Ogre::SceneNode *m_scene_node;
	Ogre::Entity *m_entity;

private:
	friend class AspectPhysics;
	friend class AspectRenderable;
};

#include "Entity381_SubClasses/Entity381Destroyer.h"
#include "Entity381_SubClasses/Entity381Carrier.h"
#include "Entity381_SubClasses/Entity381Speedboat.h"
#include "Entity381_SubClasses/Entity381Frigate.h"
#include "Entity381_SubClasses/Entity381Flying.h"

#endif
