#ifndef CAMERACONTROLLER_H_
#define CAMERACONTROLLER_H_

#include <OgreSceneManager.h>
#include <OgreCamera.h>

#include <OISEvents.h>
#include <OISKeyboard.h>

#include "Entity381.h"

class CameraController {

public:
	CameraController(Ogre::Camera *camera, Ogre::SceneManager *scene_manager, const Ogre::Vector3 &position = Ogre::Vector3(0.f, 0.f, 0.f),
		const Ogre::Vector3 &focus_direction = Ogre::Vector3(0.f, 0.f, -1.f));
	~CameraController(void);

public:
	void SetMinimumY(float min_y);

	void InjectKeyDown(const OIS::KeyEvent &key_down);
	void InjectKeyUp(const OIS::KeyEvent &key_up);

	void FollowEntity(const Entity381 *entity);
	void StopFollowingEntity(void);
	bool IsFollowingEntity(void) const;

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

	const Entity381 *m_following_entity;
};

#endif
