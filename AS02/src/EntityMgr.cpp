/*
 -----------------------------------------------------------------------------
 Filename: EntityMgr.cpp
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains implementation of EntityMgr class
 */

#include "EntityMgr.h"

EntityMgr::EntityMgr(Ogre::SceneManager *scene_manager) :
	m_selected(-1), m_scene_manager(scene_manager) {
}

EntityMgr::~EntityMgr(void) {
	for (Entity381 *e : m_entities)
		delete e;
}

Entity381* EntityMgr::CreateEntityOfTypeAtPosition(const EntityType type, const Ogre::Vector3 &position) {
	if (type == EntityType::CUBE)
		m_entities.push_back(new Entity381Cube(m_entities.size(), std::to_string(m_entities.size()), m_scene_manager, position));
	else if (type == EntityType::SPHERE)
		m_entities.push_back(new Entity381Sphere(m_entities.size(), std::to_string(m_entities.size()), m_scene_manager, position));
	else
		return nullptr; //unknown type

	return m_entities.back();
}

bool EntityMgr::selectNextEntity(void) {
	if (m_entities.size() < 0) {
		m_selected = -1;
		return false;
	}

	if (m_selected >= 0)
		m_entities[m_selected]->showBoundingBox(false);

	++m_selected %= m_entities.size();
	m_entities[m_selected]->showBoundingBox(true);
	return true;
}

bool EntityMgr::setSelectedEntityVelocity(const Ogre::Vector3& velocity, bool accumulate) {
	if (m_selected < 0)
		return false;

	m_entities[m_selected]->setVelocity(velocity, accumulate);
	return true;
}

void EntityMgr::Tick(float dt) {
	for (Entity381 *e : m_entities)
		e->Tick(dt);
}

