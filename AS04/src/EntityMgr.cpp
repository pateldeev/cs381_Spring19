#include "EntityMgr.h"

#include "Engine.h"
#include "GfxMgr.h"

EntityMgr::EntityMgr(Engine *engine) :
	Mgr(engine), m_selected_main(-1), m_graphics_scene_manager(nullptr) {
}

EntityMgr::~EntityMgr(void) {

}

void EntityMgr::Init(void) {
	m_selected_main = -1;
	m_entities.clear();
	m_selected_group.clear();
}

void EntityMgr::LoadLevel(void) {
	m_graphics_scene_manager = m_engine->m_gfx_mgr->GetOgreSceneManger();
}

void EntityMgr::Tick(float dt) {
	for (Entity381 *e : m_entities)
		e->Tick(dt);
}

void EntityMgr::Stop(void) {
	for (Entity381 *e : m_entities)
		delete e;
}

Entity381* EntityMgr::CreateEntityOfTypeAtPosition(const EntityType type, const Ogre::Vector3 &position) {
	if (type == EntityType::DESTROYER)
		m_entities.push_back(new Entity381Destroyer(m_entities.size(), std::to_string(m_entities.size()), m_graphics_scene_manager, position));
	else if (type == EntityType::CARRIER)
		m_entities.push_back(new Entity381Carrier(m_entities.size(), std::to_string(m_entities.size()), m_graphics_scene_manager, position));
	else if (type == EntityType::SPEEDBOAT)
		m_entities.push_back(new Entity381Speedboat(m_entities.size(), std::to_string(m_entities.size()), m_graphics_scene_manager, position));
	else if (type == EntityType::FRIGATE)
		m_entities.push_back(new Entity381Frigate(m_entities.size(), std::to_string(m_entities.size()), m_graphics_scene_manager, position));
	else if (type == EntityType::ALIEN)
		m_entities.push_back(new Entity381Alien(m_entities.size(), std::to_string(m_entities.size()), m_graphics_scene_manager, position));
	else
		return nullptr; //unknown type

	return m_entities.back();
}

bool EntityMgr::SelectNextEntity(void) {
	if (m_entities.size() <= 0) {
		m_selected_main = -1;
		return false;
	}

	ChangeSelectedEntity((m_selected_main + 1) % m_entities.size());
	return true;
}

bool EntityMgr::SelectPreviousEntity(void) {
	if (m_entities.size() < 0 || m_selected_main >= int(m_entities.size())) {
		m_selected_main = -1;
		return false;
	}

	int previous_position = m_selected_main - 1;
	if (previous_position < 0)
		previous_position = m_entities.size() - 1;

	ChangeSelectedEntity(previous_position);
	return true;
}

bool EntityMgr::SelectEntityByName(const std::string &name) {
	for (unsigned int i = 0; i < m_entities.size(); ++i) {
		if (m_entities[i]->GetName() == name) {
			ChangeSelectedEntity(i);
			return true;
		}
	}
	return false; //entity not found
}

const Entity381* EntityMgr::GetSelectedEntity(void) const {
	return (m_selected_main >= 0) ? m_entities[m_selected_main] : nullptr;
}

bool EntityMgr::AddEntityToGroup(const std::string &name) {
	for (unsigned int i = 0; i < m_entities.size(); ++i) {
		if (m_entities[i]->GetName() == name) {
			if (int(i) != m_selected_main) {
				m_selected_group.push_back(i);
				m_entities[i]->ShowBoundingBox(true);
			}
			return true;
		}
	}
	return false; //entity not found
}

void EntityMgr::ClearGroup(void) {
	for (unsigned int i : m_selected_group)
		m_entities[i]->ShowBoundingBox(false);
	m_selected_group.clear();
}

bool EntityMgr::ChangeSelectedDesiredSpeed(float amount) {
	if (m_selected_main < 0)
		return false;

	m_entities[m_selected_main]->ChangeDesiredSpeed(amount);
	return true;
}

bool EntityMgr::ChangeSelectedDesiredHeading(float amount) {
	if (m_selected_main < 0)
		return false;

	m_entities[m_selected_main]->ChangeDesiredHeading(amount);
	return true;
}

bool EntityMgr::ChangeSelectedDesiredHeight(float amount) {
	if (m_selected_main < 0)
		return false;

	return m_entities[m_selected_main]->ChangeDesiredHeight(amount);
}

bool EntityMgr::ResetSelectedSpeedAndHeading(void) {
	if (m_selected_main < 0)
		return false;

	std::pair<float, float> heading_speed = m_entities[m_selected_main]->GetDesiredHeadingAndSpeed();
	m_entities[m_selected_main]->ChangeDesiredHeading(-heading_speed.first);
	m_entities[m_selected_main]->ChangeDesiredSpeed(-heading_speed.second);
	return true;
}

bool EntityMgr::ChangeGroupDesiredSpeed(float amount) {
	for (unsigned int i : m_selected_group)
		m_entities[i]->ChangeDesiredSpeed(amount);
	return m_selected_group.size();
}

bool EntityMgr::ChangeGroupDesiredHeading(float amount) {
	for (unsigned int i : m_selected_group)
		m_entities[i]->ChangeDesiredHeading(amount);
	return m_selected_group.size();
}

bool EntityMgr::ResetGroupSpeedAndHeading(void) {
	for (unsigned int i : m_selected_group) {
		std::pair<float, float> heading_speed = m_entities[i]->GetDesiredHeadingAndSpeed();
		m_entities[i]->ChangeDesiredHeading(-heading_speed.first);
		m_entities[i]->ChangeDesiredSpeed(-heading_speed.second);
	}
	return m_selected_group.size();
}

bool EntityMgr::DisplaySelectedSpeedAndHeading(void) const {
	if (m_selected_main < 0)
		return false;

	std::pair<float, float> heading_speed = m_entities[m_selected_main]->GetDesiredHeadingAndSpeed();

	std::cout << "Ship: " << m_entities[m_selected_main]->GetName() << " movement set | heading " << heading_speed.first << " at speed "
		<< heading_speed.second << std::endl;

	return true;
}

void EntityMgr::ChangeSelectedEntity(unsigned int position) {
	if (m_selected_main >= 0)
		m_entities[m_selected_main]->ShowBoundingBox(false);

	m_selected_main = position;

	m_entities[m_selected_main]->ShowBoundingBox(true);
}
