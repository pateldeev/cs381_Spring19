/*
 -----------------------------------------------------------------------------
 Filename: CameraController.cpp
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains implementation of CameraController class
 */

#include "CameraController.h"

CameraController::CameraController(Ogre::Camera *camera, Ogre::SceneManager *scene_manager, const Ogre::Vector3 &position,
	const Ogre::Vector3 &focus_direction) :
	m_camera_node(nullptr), m_move_x(0), m_move_z(0), m_move_y(0), m_lshift(false), m_yaw(0), m_pitch(0), m_apply_min_y(false), m_min_y(0) {

	camera->setPosition(Ogre::Vector3(0.f)); //reset camera's internal position

	m_camera_node = scene_manager->getRootSceneNode()->createChildSceneNode();
	m_camera_node->lookAt(focus_direction, Ogre::Node::TransformSpace::TS_WORLD);
	m_camera_node->translate(position);

	m_camera_node->attachObject(camera);
}

CameraController::~CameraController(void) {

}

void CameraController::setMinimumY(float min_y) {
	m_apply_min_y = true;
	m_min_y = min_y;
}

void CameraController::injectKeyDown(const OIS::KeyEvent &key_down) {
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

void CameraController::injectKeyUp(const OIS::KeyEvent &key_up) {
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

void CameraController::Tick(float dt) {
	const float move_scalar = 300 * dt;
	m_camera_node->translate(move_scalar * m_move_x, move_scalar * m_move_y, move_scalar * m_move_z, Ogre::Node::TransformSpace::TS_LOCAL);

	//rotate camera as needed
	const Ogre::Radian yaw(m_yaw * 0.4 * dt);
	const Ogre::Radian pitch(m_pitch * 0.4 * dt);
	m_camera_node->yaw(yaw, Ogre::Node::TransformSpace::TS_LOCAL);
	m_camera_node->pitch(pitch, Ogre::Node::TransformSpace::TS_LOCAL);

	if (m_apply_min_y && m_camera_node->getPosition().y < m_min_y)
		m_camera_node->translate(0, m_min_y - m_camera_node->getPosition().y, 0, Ogre::Node::TransformSpace::TS_LOCAL);
}

