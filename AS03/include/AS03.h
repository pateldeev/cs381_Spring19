/*
 -----------------------------------------------------------------------------
 Filename: AS03.h
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains declaration of AS03 class
 */

#ifndef AS03_H_
#define AS03_H_

#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include "CameraController.h"
#include "EntityMgr.h"

class AS03: public Ogre::WindowEventListener, public Ogre::FrameListener, public OIS::KeyListener, public OIS::MouseListener {

public:
	AS03(const std::string &window_name = "Main_Render_Window", int surface_height = 0);
	virtual ~AS03(void);

	//TutorialApplication is not meant to be copied or moved - for simplicity
	AS03(const AS03&) = delete;
	AS03(AS03&&) = delete;
	AS03& operator=(const AS03&) = delete;
	AS03& operator=(AS03&&) = delete;

public:
	bool go(void);

private:
	void setupResources(void);
	void setupScene(void);
	void setupOIS(void);

	//called up setupScene
	void setupCamera(void);
	void setupLighting(void);
	void setupOcean(void);
	void addIsland(const Ogre::Vector3 &location, const std::string &name);
	void setupSky(void);
	void setupEntities(void);

	virtual void windowResized(Ogre::RenderWindow *rw) override final;
	virtual void windowClosed(Ogre::RenderWindow *rw) override final;

	virtual bool keyPressed(const OIS::KeyEvent &arg) override final;
	virtual bool keyReleased(const OIS::KeyEvent &arg) override final;

	virtual bool mouseMoved(const OIS::MouseEvent &arg) override final;
	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) override final;
	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) override final;

	virtual bool frameRenderingQueued(const Ogre::FrameEvent &e) override final;
	bool processUnbufferedInput(const Ogre::FrameEvent &e);

	void updateVelocity(float dt);

private:
	std::string m_window_name;

	Ogre::Root *m_root;
	std::string m_resources_cfg;
	std::string m_plugins_cfg;

	Ogre::RenderWindow *m_window;
	Ogre::SceneManager *m_scene_manager;
	Ogre::Camera *m_camera;

	OIS::InputManager *m_input_manager;
	OIS::Keyboard *m_keyboard;
	OIS::Mouse *m_mouse;

	float m_ocean_height;
	CameraController *m_camera_controller;

	float m_velocity_update_cooldown;
	EntityMgr *m_entity_manager;

	Ogre::RaySceneQuery *m_ray_query;
};

//---------------------------------------------------------------------------

#endif  /* AS03_H_ */

//---------------------------------------------------------------------------
