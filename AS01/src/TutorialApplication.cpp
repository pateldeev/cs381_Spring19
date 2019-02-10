/*
 -----------------------------------------------------------------------------
 Filename:    TutorialApplication.cpp
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

#include "TutorialApplication.h"

//---------------------------------------------------------------------------
TutorialApplication::TutorialApplication(const std::string &windowName, int surfaceHeight) :
	BaseApplication(windowName), mSurfaceHeight(surfaceHeight), mObjSelected(0), mCameraVelocity(0.f), mArrowUPressed(false), mArrowDPressed(false),
	mArrowRPressed(false), mArrowLPressed(false), mPgUPressed(false), mPgDPressed(false), mUpdateRotation(false) {
}

//---------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void) {
}

//---------------------------------------------------------------------------
void TutorialApplication::createScene(void) {
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.8, 0.8, 0.8));
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);

	mCamera->setPosition(Ogre::Vector3(0, 0, 0)); //set camera position
	mCamera->setOrientation(Ogre::Quaternion(0.7, -0.7, 0, 0));

	char objName[25];
	for (int i = 0; i < OBJ_TOTAL; ++i) {
		mObjects[i] = mSceneMgr->createEntity("banshee.mesh");
		sprintf(objName, "mObject[%d]", i);
		mObjectNodes[i] = mSceneMgr->getRootSceneNode()->createChildSceneNode(objName);
		mObjectNodes[i]->attachObject(mObjects[i]);
		mObjectNodes[i]->translate(Ogre::Vector3(100 * (i % OBJ_PER_ROW), mSurfaceHeight + 50, 100 * int(i / OBJ_PER_ROW)));
		mObjectNodes[i]->scale(Ogre::Vector3(2.5));
	}
	mObjectNodes[mObjSelected]->showBoundingBox(true);
	mObjVelocities[mObjSelected] = Ogre::Vector3(0.0); //create entry for velocity - so we know to update

	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 10000, 10000, 20, 20,
		true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	Ogre::SceneNode *floorNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity *floorEntity = mSceneMgr->createEntity("ground");
	floorNode->attachObject(floorEntity);

	floorEntity->setCastShadows(false);
	floorEntity->setMaterialName("Examples/Rockwall");
	floorNode->translate(Ogre::Vector3(0, mSurfaceHeight, 0));
}

bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent &e) {
	if (!processUnbufferedInput(e))
		return false;

	return BaseApplication::frameRenderingQueued(e);
}

bool TutorialApplication::keyPressed(const OIS::KeyEvent &arg) {
	static const float VELOCITY_CHANGE = 25;

	switch (arg.key) {

	case OIS::KC_UP:
		mObjVelocities[mObjSelected].z += VELOCITY_CHANGE;
		mArrowUPressed = mUpdateRotation = true;
		break;

	case OIS::KC_DOWN:
		mObjVelocities[mObjSelected].z -= VELOCITY_CHANGE;
		mArrowDPressed = mUpdateRotation = true;
		break;

	case OIS::KC_RIGHT:
		mObjVelocities[mObjSelected].x += VELOCITY_CHANGE;
		mArrowRPressed = mUpdateRotation = true;
		break;

	case OIS::KC_LEFT:
		mObjVelocities[mObjSelected].x -= VELOCITY_CHANGE;
		mArrowLPressed = mUpdateRotation = true;
		break;

	case OIS::KC_PGUP:
		mObjVelocities[mObjSelected].y += VELOCITY_CHANGE;
		mPgUPressed = mUpdateRotation = true;
		break;

	case OIS::KC_PGDOWN:
		mObjVelocities[mObjSelected].y -= VELOCITY_CHANGE;
		mPgDPressed = mUpdateRotation = true;
		break;

	case OIS::KC_SPACE:
		mObjVelocities[mObjSelected] = Ogre::Vector3(0.0);
		break;

	case OIS::KC_TAB:
		mObjectNodes[mObjSelected]->showBoundingBox(false);

		if (mObjVelocities[mObjSelected].length() < 0.1)
			mObjVelocities.erase(mObjSelected); //remove entry of velocity is zero - update function doesn't have to worry about it.

		if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			mObjSelected = (mObjSelected) ? mObjSelected - 1 : OBJ_TOTAL - 1;
		else
			++mObjSelected %= OBJ_TOTAL;

		mObjectNodes[mObjSelected]->showBoundingBox(true);
		mObjVelocities[mObjSelected]; //create entry for velocity - so we know to update
		mUpdateRotation = false;
		break;

	case OIS::KC_A:
		--mCameraVelocity.x;
		break;

	case OIS::KC_D:
		++mCameraVelocity.x;
		break;

	case OIS::KC_S:
		--mCameraVelocity.z;
		break;

	case OIS::KC_W:
		++mCameraVelocity.z;
		break;

	case OIS::KC_E:
		++mCameraVelocity.y;
		break;

	case OIS::KC_F:
		--mCameraVelocity.y;
		break;

	default:
		break;
	}

	return BaseApplication::keyPressed(arg);
}

bool TutorialApplication::keyReleased(const OIS::KeyEvent &arg) {
	switch (arg.key) {

	case OIS::KC_UP:
		mArrowUPressed = false;
		break;

	case OIS::KC_DOWN:
		mArrowDPressed = false;
		break;

	case OIS::KC_RIGHT:
		mArrowRPressed = false;
		break;

	case OIS::KC_LEFT:
		mArrowLPressed = false;
		break;

	case OIS::KC_PGUP:
		mPgUPressed = false;
		break;

	case OIS::KC_PGDOWN:
		mPgDPressed = false;
		break;

	case OIS::KC_A:
		++mCameraVelocity.x;
		break;

	case OIS::KC_D:
		--mCameraVelocity.x;
		break;

	case OIS::KC_S:
		++mCameraVelocity.z;
		break;

	case OIS::KC_W:
		--mCameraVelocity.z;
		break;

	case OIS::KC_E:
		--mCameraVelocity.y;
		break;

	case OIS::KC_F:
		++mCameraVelocity.y;
		break;

	default:
		break;
	}

	return BaseApplication::keyReleased(arg);
}

bool TutorialApplication::processUnbufferedInput(const Ogre::FrameEvent &e) {
	for (const std::pair<int, Ogre::Vector3> &v : mObjVelocities)
		mObjectNodes[v.first]->translate(v.second * e.timeSinceLastEvent);

	if (mCameraVelocity.length() > 0.01)
		mCamera->setPosition(mCamera->getPosition() + 300 * mCameraVelocity.normalisedCopy() * e.timeSinceLastEvent);

	if (mUpdateRotation) {
		mObjectNodes[mObjSelected]->resetOrientation();
		Ogre::Matrix3 objRotation;

		Ogre::Radian yRot(std::atan2(-mObjVelocities[mObjSelected].z, mObjVelocities[mObjSelected].x));
		objRotation.FromEulerAnglesXYZ(Ogre::Radian(0), Ogre::Radian(yRot), Ogre::Radian(0));
		mObjectNodes[mObjSelected]->rotate(Ogre::Quaternion(objRotation));

		Ogre::Radian zRot(3.14 * mObjVelocities[mObjSelected].normalisedCopy().y / 2);
		objRotation.FromEulerAnglesXYZ(Ogre::Radian(0), Ogre::Radian(0), Ogre::Radian(zRot));
		mObjectNodes[mObjSelected]->rotate(Ogre::Quaternion(objRotation));

		mUpdateRotation = false;
	}
	return true;
}
