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
TutorialApplication::TutorialApplication(const std::string &windowName) :
	BaseApplication(windowName) {
}

//---------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void) {
}

//---------------------------------------------------------------------------
void TutorialApplication::createScene(void) {
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	mCamera->setPosition(0, 47, 222);

	Ogre::Light *light = mSceneMgr->createLight("MainLight");
	light->setPosition(20.0, 80.0, 50.0);

	Ogre::Entity *ogreEntity = mSceneMgr->createEntity("ogrehead.mesh");
	Ogre::SceneNode *ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ogreNode->attachObject(ogreEntity);
	ogreNode->showBoundingBox(true);

	Ogre::Entity *ogreEntity2 = mSceneMgr->createEntity("ogrehead.mesh");
	Ogre::SceneNode *ogreNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(84, 48, 0));
	ogreNode2->attachObject(ogreEntity2);
	ogreNode2->showBoundingBox(true);

	Ogre::Entity *ogreEntity3 = mSceneMgr->createEntity("ogrehead.mesh");
	Ogre::SceneNode *ogreNode3 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ogreNode3->setPosition(Ogre::Vector3(0, 104, 0));
	ogreNode3->setScale(2, 1.2, 1);
	ogreNode3->attachObject(ogreEntity3);
	ogreNode3->showBoundingBox(true);

	Ogre::Entity *ogreEntity4 = mSceneMgr->createEntity("ogrehead.mesh");
	Ogre::SceneNode *ogreNode4 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ogreNode4->setPosition(-84, 48, 0);
	ogreNode4->roll(Ogre::Degree(-90));
	ogreNode4->attachObject(ogreEntity4);
	ogreNode4->showBoundingBox(true);
}
