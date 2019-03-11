#include "CameraController.h"

CameraController::CameraController(Ogre::Camera *camera, Ogre::SceneManager *scene_manager, const Ogre::Vector3 &position,
	const Ogre::Vector3 &focus_direction) :
	m_camera_node(nullptr), m_move_x(0), m_move_z(0), m_move_y(0), m_lshift(false), m_yaw(0), m_pitch(0), m_apply_min_y(false), m_min_y(0),
	m_following_entity(nullptr) {

	m_camera_node = scene_manager->getRootSceneNode()->createChildSceneNode();
	m_camera_node->lookAt(focus_direction, Ogre::Node::TransformSpace::TS_WORLD);
	m_camera_node->translate(position);

	m_camera_node->attachObject(camera);
}

CameraController::~CameraController(void) {

}

void CameraController::SetMinimumY(float min_y) {
	m_apply_min_y = true;
	m_min_y = min_y;
}

void CameraController::InjectKeyDown(const OIS::KeyEvent &key_down) {
	if (key_down.key == OIS::KC_LSHIFT) { //handle change in left shift key
		m_move_x = m_move_z = m_move_y = 0;
		m_lshift = true;
		return;
	}

	if (!m_lshift) { //adjust camera velocity
		if (key_down.key == OIS::KC_A)
			m_move_x = -1;
		else if (key_down.key == OIS::KC_D)
			m_move_x = 1;
		else if (key_down.key == OIS::KC_S)
			m_move_z = 1;
		else if (key_down.key == OIS::KC_W)
			m_move_z = -1;
		else if (key_down.key == OIS::KC_E)
			m_move_y = 1;
		else if (key_down.key == OIS::KC_F)
			m_move_y = -1;
	} else { //adjust camera yaw
		if (key_down.key == OIS::KC_A)
			m_yaw = 1;
		else if (key_down.key == OIS::KC_D)
			m_yaw = -1;
		else if (key_down.key == OIS::KC_W)
			m_pitch = 1;
		else if (key_down.key == OIS::KC_S)
			m_pitch = -1;
	}
}

void CameraController::InjectKeyUp(const OIS::KeyEvent &key_up) {
	if (key_up.key == OIS::KC_LSHIFT) { //handle change in left shift key
		m_yaw = m_pitch = 0;
		m_lshift = false;
		return;
	}

	if (!m_lshift) { //adjust camera velocity
		if (key_up.key == OIS::KC_A || key_up.key == OIS::KC_D)
			m_move_x = 0;
		else if (key_up.key == OIS::KC_S || key_up.key == OIS::KC_W)
			m_move_z = 0;
		else if (key_up.key == OIS::KC_E || key_up.key == OIS::KC_F)
			m_move_y = 0;
	} else { //adjust camera yaw
		if (key_up.key == OIS::KC_A || key_up.key == OIS::KC_D)
			m_yaw = 0;
		else if (key_up.key == OIS::KC_W || key_up.key == OIS::KC_S)
			m_pitch = 0;
	}
}

void CameraController::FollowEntity(const Entity381 *entity) {
	m_following_entity = entity;
}

void CameraController::StopFollowingEntity(void) {
	m_following_entity = nullptr;
}

bool CameraController::IsFollowingEntity(void) const {
	return (m_following_entity != nullptr);
}

void CameraController::Tick(float dt) {
	if (!m_following_entity) {
		const float move_scalar = 300 * dt;
		m_camera_node->translate(move_scalar * m_move_x, move_scalar * m_move_y, move_scalar * m_move_z, Ogre::Node::TransformSpace::TS_LOCAL);

		//rotate camera as needed
		const Ogre::Radian yaw(m_yaw * 0.4 * dt);
		const Ogre::Radian pitch(m_pitch * 0.4 * dt);
		m_camera_node->yaw(yaw, Ogre::Node::TransformSpace::TS_LOCAL);
		m_camera_node->pitch(pitch, Ogre::Node::TransformSpace::TS_LOCAL);

		if (m_apply_min_y && m_camera_node->getPosition().y < m_min_y)
			m_camera_node->translate(0, m_min_y - m_camera_node->getPosition().y, 0, Ogre::Node::TransformSpace::TS_LOCAL);
	} else {
		Ogre::Vector3 entity_size = m_following_entity->GetBoudingBox().getSize();

		Ogre::Vector3 entity_loc = m_following_entity->GetEntityPosition();
		entity_loc.y += (1.6 * entity_size.y);
		m_camera_node->setPosition(entity_loc);

		m_camera_node->resetOrientation();
		m_camera_node->yaw(Ogre::Degree(m_following_entity->GetHeadingAndSpeed().first - 90));

		m_camera_node->translate(0.f, 0.f, 1.5 * std::max(entity_size.x, entity_size.z), Ogre::Node::TransformSpace::TS_LOCAL);
	}
}
