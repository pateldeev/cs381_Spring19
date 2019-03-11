#ifndef GFXMGR_H_
#define GFXMGR_H_

#include "Mgr.h"

#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>

class GfxMgr: public Mgr {

public:
	GfxMgr(Engine *engine);
	virtual ~GfxMgr(void);

public:
	virtual void Init(void) override final;
	virtual void LoadLevel(void) override final;
	virtual void Tick(float dt) override final;
	virtual void Stop(void) override final;

public:
	Ogre::RenderWindow* GetOrgreRenderWindow(void);
	Ogre::SceneManager* GetOgreSceneManger(void);
	Ogre::Camera* GetOgreCamera(void);

private:
	void SetupOgreResources(void);
	void SetupOgreScene(void);
	void SetupOgreCamera(void);
	void SetupOgreLighting(void);

private:
	std::string m_window_name;

	Ogre::Root *m_root;
	std::string m_resources_cfg;
	std::string m_plugins_cfg;

	Ogre::RenderWindow *m_window;
	Ogre::SceneManager *m_scene_manager;
	Ogre::Camera *m_camera;
};

#endif
