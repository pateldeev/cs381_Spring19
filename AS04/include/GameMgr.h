#ifndef GAMEMGR_H_
#define GAMEMGR_H_

#include "Mgr.h"

#include "CameraController.h"

#include <OISMouse.h>

class EntityMgr;

class GameMgr: public Mgr {

public:
	GameMgr(Engine *engine);
	virtual ~GameMgr(void);

public:
	virtual void Init(void) override final;
	virtual void LoadLevel(void) override final;
	virtual void Tick(float dt) override final;
	virtual void Stop(void) override final;

public:
	void InjectKeyDown(const OIS::KeyEvent &key_down);
	void InjectKeyUp(const OIS::KeyEvent &key_up);
	void InjectMouseClick(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

private:
	void SetupCameraController(void);
	void SetupSky(void);
	void SetupOcean(void);
	void SetupShips(void);

	void UpdateSelectedEntities(float dt);

private:
	Ogre::SceneManager *m_graphics_scene_manager;

	EntityMgr *m_entity_mgr;

	int m_ocean_height;
	CameraController *m_camera_controller;

	float m_velocity_update_cooldown;
	Ogre::RaySceneQuery *m_ray_query;
};

#endif
