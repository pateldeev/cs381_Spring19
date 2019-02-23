/*
 -----------------------------------------------------------------------------
 Filename: EntityMgr.h
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains declaration of EntityMgr class
 */

#include "Entity381.h"

#include <vector>

#ifndef ENTITYMGR_H_
#define ENTITYMGR_H_

class EntityMgr {

public:
	EntityMgr(Ogre::SceneManager *scene_manager);
	~EntityMgr(void);

	//EntityMgr is not meant to be copied or moved - for simplicity
	EntityMgr(const EntityMgr&) = delete;
	EntityMgr(EntityMgr&&) = delete;
	EntityMgr& operator=(const EntityMgr&) = delete;
	EntityMgr& operator=(EntityMgr&&) = delete;

	Entity381* CreateEntityOfTypeAtPosition(const EntityType type, const Ogre::Vector3 &position = Ogre::Vector3(0.f));

	bool selectNextEntity(void); //returns false if no entities to select

	bool setSelectedEntityVelocity(const Ogre::Vector3 &velocity, bool accumulate = true); //returns false if no selected entity

	void Tick(float dt);

private:
	std::vector<Entity381*> m_entities;
	int m_selected; //-1 -> nothing selected

	Ogre::SceneManager *m_scene_manager;

};

#endif  /* ENTITYMGR_H_ */
