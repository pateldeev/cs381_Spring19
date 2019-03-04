/*
 -----------------------------------------------------------------------------
 Filename: TutorialApplication.h
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains declaration of TutorialApplication class
 */

#ifndef TUTORIALAPPLICATION_H_
#define TUTORIALAPPLICATION_H_

#include "BaseApplication.h"
#include "CameraController.h"
#include "EntityMgr.h"

class TutorialApplication: public BaseApplication {

public:
	TutorialApplication(const std::string &windowName = "TutorialApplication Render Window", int surface_height = 0);
	virtual ~TutorialApplication(void);

	//TutorialApplication is not meant to be copied or moved - for simplicity
	TutorialApplication(const TutorialApplication&) = delete;
	TutorialApplication(TutorialApplication&&) = delete;
	TutorialApplication& operator=(const TutorialApplication&) = delete;
	TutorialApplication& operator=(TutorialApplication&&) = delete;

protected:
	virtual void createScene(void) override final;

	virtual bool frameRenderingQueued(const Ogre::FrameEvent &e) override final;

	virtual bool keyPressed(const OIS::KeyEvent &arg) override final;
	virtual bool keyReleased(const OIS::KeyEvent &arg) override final;

	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) override final;

private:
	bool processUnbufferedInput(const Ogre::FrameEvent &e);

	void setupLighting(void);
	void setupCamera(void);
	void setupGround(void);
	void setupSky(void);

	void updateVelocity(float dt);

private:
	CameraController *m_camera_controller;

	EntityMgr *m_entity_manager;

	float m_ocean_height;

	float m_velocity_update_cooldown;
};

//---------------------------------------------------------------------------

#endif  /* TUTORIALAPPLICATION_H_ */

//---------------------------------------------------------------------------
