#include "Entity381.h"

Entity381::~Entity381(void) {
	for (Aspect *a : m_aspects)
		delete a;
}

void Entity381::Tick(float dt) {
	for (Aspect *a : m_aspects)
		a->Tick(dt);

	if (m_flying) {
		static_cast<Entity381Flying*>(this)->TickHeight(dt);
	}
}

void Entity381::ShowBoundingBox(bool show) {
	m_scene_node->showBoundingBox(show);
}

std::string Entity381::GetName(void) const {
	return m_name;
}

void Entity381::ChangeDesiredSpeed(float amount) {
	m_speed_desired += amount;

	if (m_speed_desired < 0)
		m_speed_desired = 0;
	else if (m_speed_desired > m_speed_max)
		m_speed_desired = m_speed_max;
}

void Entity381::ChangeDesiredHeading(float amount) {
	amount = std::fmod(amount, 360); //account for possibility of use giving more than 1 full rotation
	m_heading_desired += amount;

	if (m_heading_desired < 0)
		m_heading_desired += 360;
	else if (m_heading_desired >= 360)
		m_heading_desired -= 360;
}

bool Entity381::ChangeDesiredHeight(float amount) {
	if (!m_flying)
		return false; //object is not flying cannot change height

	static_cast<Entity381Flying *>(this)->ChangeDesiredHeight(amount);
	return true;
}

std::pair<float, float> Entity381::GetDesiredHeadingAndSpeed(void) const {
	return std::make_pair(m_heading_desired, m_speed_desired);
}

std::pair<float, float> Entity381::GetHeadingAndSpeed(void) const {
	return std::make_pair(m_heading, m_speed);
}

Ogre::Vector3 Entity381::GetEntityPosition(void) const {
	return m_scene_node->_getDerivedPosition();
}

const Ogre::AxisAlignedBox& Entity381::GetBoudingBox(void) const{
	return m_scene_node->_getWorldAABB();
}

Entity381::Entity381(unsigned int id, const std::string &entity_name, const std::string &mesh_file, Ogre::SceneManager *scene_manager,
	const Ogre::Vector3 &position, const Ogre::Vector3 &scale) :
	m_speed_max(0.f), m_acceleration(0.f), m_turning_rate(0.f), m_flying(false), m_position(position), m_velocity(0.f), m_id(id), m_name(entity_name),
	m_mesh_file(mesh_file), m_speed(0.f), m_speed_desired(0.f), m_heading(0.f), m_heading_desired(0.f), m_scene_node(nullptr), m_entity(nullptr) {

	m_entity = scene_manager->createEntity(m_mesh_file);

	m_scene_node = scene_manager->getRootSceneNode()->createChildSceneNode(m_name, position);
	m_scene_node->scale(scale);
	m_scene_node->attachObject(m_entity);
}
