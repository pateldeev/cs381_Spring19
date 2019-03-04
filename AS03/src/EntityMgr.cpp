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
	m_selected_main(-1), m_scene_manager(scene_manager) {
}

EntityMgr::~EntityMgr(void) {
	for (Entity381 *e : m_entities)
		delete e;
}

Entity381* EntityMgr::CreateEntityOfTypeAtPosition(const EntityType type, const Ogre::Vector3 &position) {
	if (type == EntityType::DESTROYER)
		m_entities.push_back(new Entity381Destroyer(m_entities.size(), std::to_string(m_entities.size()), m_scene_manager, position));
	else if (type == EntityType::CARRIER)
		m_entities.push_back(new Entity381Carrier(m_entities.size(), std::to_string(m_entities.size()), m_scene_manager, position));
	else if (type == EntityType::SPEEDBOAT)
		m_entities.push_back(new Entity381Speedboat(m_entities.size(), std::to_string(m_entities.size()), m_scene_manager, position));
	else if (type == EntityType::FRIGATE)
		m_entities.push_back(new Entity381Frigate(m_entities.size(), std::to_string(m_entities.size()), m_scene_manager, position));
	else if (type == EntityType::ALIEN)
		m_entities.push_back(new Entity381Alien(m_entities.size(), std::to_string(m_entities.size()), m_scene_manager, position));
	else
		return nullptr; //unknown type

	return m_entities.back();
}

bool EntityMgr::selectNextEntity(void) {
	if (m_entities.size() <= 0) {
		m_selected_main = -1;
		return false;
	}

	changeSelectedEntity((m_selected_main + 1) % m_entities.size());
	return true;
}

bool EntityMgr::selectPreviousEntity(void) {
	if (m_entities.size() < 0 || m_selected_main >= int(m_entities.size())) {
		m_selected_main = -1;
		return false;
	}

	int previous_position = m_selected_main - 1;
	if (previous_position < 0)
		previous_position = m_entities.size() - 1;

	changeSelectedEntity(previous_position);
	return true;
}

bool EntityMgr::selectEntityByName(const std::string &name) {
	for (unsigned int i = 0; i < m_entities.size(); ++i) {
		if (m_entities[i]->getName() == name) {
			changeSelectedEntity(i);
			return true;
		}
	}
	return false; //entity not found
}

bool EntityMgr::addEntityToGroup(const std::string &name) {
	for (unsigned int i = 0; i < m_entities.size(); ++i) {
		if (m_entities[i]->getName() == name) {
			if (int(i) != m_selected_main) {
				m_selected_group.push_back(i);
				m_entities[i]->showBoundingBox(true);
			}
			return true;
		}
	}
	return false; //entity not found
}

void EntityMgr::clearGroup(void) {
	for (unsigned int i : m_selected_group)
		m_entities[i]->showBoundingBox(false);
	m_selected_group.clear();
}

bool EntityMgr::changeSelectedDesiredSpeed(float amount) {
	if (m_selected_main < 0)
		return false;

	m_entities[m_selected_main]->changeDesiredSpeed(amount);
	return true;
}

bool EntityMgr::changeSelectedDesiredHeading(float amount) {
	if (m_selected_main < 0)
		return false;

	m_entities[m_selected_main]->changeDesiredHeading(amount);
	return true;
}

bool EntityMgr::resetSelectedSpeedAndHeading(void) {
	if (m_selected_main < 0)
		return false;

	std::pair<float, float> heading_speed = m_entities[m_selected_main]->getDesiredHeadingAndSpeed();
	m_entities[m_selected_main]->changeDesiredHeading(-heading_speed.first);
	m_entities[m_selected_main]->changeDesiredSpeed(-heading_speed.second);
	return true;
}

bool EntityMgr::changeGroupDesiredSpeed(float amount) {
	for (unsigned int i : m_selected_group)
		m_entities[i]->changeDesiredSpeed(amount);
	return m_selected_group.size();
}

bool EntityMgr::changeGroupDesiredHeading(float amount) {
	for (unsigned int i : m_selected_group)
		m_entities[i]->changeDesiredHeading(amount);
	return m_selected_group.size();
}

bool EntityMgr::resetGroupSpeedAndHeading(void) {
	for (unsigned int i : m_selected_group) {
		std::pair<float, float> heading_speed = m_entities[i]->getDesiredHeadingAndSpeed();
		m_entities[i]->changeDesiredHeading(-heading_speed.first);
		m_entities[i]->changeDesiredSpeed(-heading_speed.second);
	}
	return m_selected_group.size();
}

bool EntityMgr::displaySelectedSpeedAndHeading(void) const {
	if (m_selected_main < 0)
		return false;

	std::pair<float, float> heading_speed = m_entities[m_selected_main]->getDesiredHeadingAndSpeed();

	std::cout << "Ship: " << m_entities[m_selected_main]->getName() << " movement set | heading " << heading_speed.first << " at speed "
		<< heading_speed.second << std::endl;

	return true;
}

void EntityMgr::Tick(float dt) {
	for (Entity381 *e : m_entities)
		e->Tick(dt);
}

void EntityMgr::changeSelectedEntity(unsigned int position) {
	if (m_selected_main >= 0)
		m_entities[m_selected_main]->showBoundingBox(false);

	m_selected_main = position;

	m_entities[m_selected_main]->showBoundingBox(true);
}

