/*
 -----------------------------------------------------------------------------
 Filename: CameraController.h
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains declaration of CameraController class
 */

#ifndef CAMERACONTROLLER_H_
#define CAMERACONTROLLER_H_

#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreCamera.h>

#include <OISEvents.h>
#include <OISKeyboard.h>

class CameraController {

public:
	CameraController(Ogre::Camera *camera, Ogre::SceneManager *scene_manager, const Ogre::Vector3 &position = Ogre::Vector3(0.f, 0.f, 0.f),
		const Ogre::Vector3 &focus_direction = Ogre::Vector3(0.f, 0.f, -1.f));
	~CameraController(void);

	void setMinimumY(float min_y);

	void injectKeyDown(const OIS::KeyEvent &key_down);
	void injectKeyUp(const OIS::KeyEvent &key_up);

	void Tick(float dt);

private:
	Ogre::SceneNode *m_camera_node;

	int m_move_x;
	int m_move_z;
	int m_move_y;

	bool m_lshift;
	int m_yaw;
	int m_pitch;

	bool m_apply_min_y;
	float m_min_y;
};

#endif /* CAMERACONTROLLER_H_ */
