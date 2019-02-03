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
	//for lighting
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5)); //global light level
	Ogre::Light *light = mSceneMgr->createLight("MainLight"); //create basic light
	light->setPosition(20.0, 80.0, 50.0);

	mCamera->setPosition(0, 47, 222); //set camera position

	//add ogre 1
	Ogre::Entity *ogreEntity = mSceneMgr->createEntity("ogrehead.mesh");
	Ogre::SceneNode *ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ogreNode->attachObject(ogreEntity);
	ogreNode->showBoundingBox(true); //show aabb bounding box around model

	//add ogre 2
	Ogre::Entity *ogreEntity2 = mSceneMgr->createEntity("ogrehead.mesh");
	Ogre::SceneNode *ogreNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(84, 48, 0));
	ogreNode2->attachObject(ogreEntity2);
	ogreNode2->showBoundingBox(true); //show aabb bounding box around model

	//add ogre 3
	Ogre::Entity *ogreEntity3 = mSceneMgr->createEntity("ogrehead.mesh");
	Ogre::SceneNode *ogreNode3 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ogreNode3->setPosition(Ogre::Vector3(0, 104, 0));
	ogreNode3->setScale(2, 1.2, 1); //scale model
	ogreNode3->attachObject(ogreEntity3);
	ogreNode3->showBoundingBox(true); //show aabb bounding box around model

	//add ogre 4
	Ogre::Entity *ogreEntity4 = mSceneMgr->createEntity("ogrehead.mesh");
	Ogre::SceneNode *ogreNode4 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ogreNode4->setPosition(-84, 48, 0);
	ogreNode4->roll(Ogre::Degree(-90)); //rotate model
	ogreNode4->attachObject(ogreEntity4);
	ogreNode4->showBoundingBox(true); //show aabb bounding box around model
}
