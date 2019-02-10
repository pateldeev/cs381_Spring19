/*
 -----------------------------------------------------------------------------
 Filename:    TutorialApplication.h
 -----------------------------------------------------------------------------

 This source file is derived from the
 ___                 __    __ _ _    _
 /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
 / \_// (_| | | |  __/  \  /\  /| |   <| |
 \___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
 |___/
 Tutorial Framework (for Ogre 1.9)
 http://www.ogre3d.org/wiki/

 Edited by: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 */

#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "BaseApplication.h"

#include <unordered_map>

//---------------------------------------------------------------------------

#define OBJ_PER_ROW 10
#define OBJ_ROWS 10
#define OBJ_TOTAL (OBJ_PER_ROW * OBJ_ROWS)

class TutorialApplication: public BaseApplication {
public:
	TutorialApplication(const std::string &windowName = "TutorialApplication Render Window", int surfaceHeight = -500);
	virtual ~TutorialApplication(void);

protected:
	virtual void createScene(void);

	virtual bool frameRenderingQueued(const Ogre::FrameEvent &e);

	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);

private:
	bool processUnbufferedInput(const Ogre::FrameEvent &e);

	int mSurfaceHeight;

	Ogre::Entity *mObjects[OBJ_TOTAL];
	Ogre::SceneNode *mObjectNodes[OBJ_TOTAL];
	int mObjSelected;
	std::unordered_map<int, Ogre::Vector3> mObjVelocities;
	Ogre::Vector3 mCameraVelocity;

	bool mArrowUPressed;
	bool mArrowDPressed;
	bool mArrowRPressed;
	bool mArrowLPressed;
	bool mPgUPressed;
	bool mPgDPressed;

	bool mUpdateRotation;
};

//---------------------------------------------------------------------------

#endif // #ifndef __TutorialApplication_h_

//---------------------------------------------------------------------------
