#include "Entity381_SubClasses/Entity381Flying.h"

Entity381Flying::~Entity381Flying(void) {

}

void Entity381Flying::ChangeDesiredHeight(float amount) {
	m_height_desired += amount;
}

void Entity381Flying::TickHeight(float dt) {
	const float ACCEPTABLE_ERROR = 0.2;
	const float max_change = m_vertical_acceleration * dt;
	if (m_height < m_height_desired - ACCEPTABLE_ERROR) {
		if (m_height < m_height_desired - max_change)
			m_height += max_change;
		else
			m_height = m_height_desired;
	}
	if (m_height > m_height_desired + ACCEPTABLE_ERROR) {
		if (m_height > m_height_desired + max_change)
			m_height -= max_change;
		else
			m_height = m_height_desired;
	}
	m_position.y = m_height;
}

Entity381Flying::Entity381Flying(unsigned int id, const std::string &name, const std::string &mesh_file, Ogre::SceneManager *scene_manager,
	const Ogre::Vector3 &position, const Ogre::Vector3 &scale) :
	Entity381(id, name, mesh_file, scene_manager, position, scale), m_vertical_acceleration(0.f), m_height(position.y), m_height_desired(m_height) {
	m_flying = true;
}
