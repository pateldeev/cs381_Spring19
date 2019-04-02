#include <Engine.h>

#include <EntityMgr.h>
#include <GameMgr.h>
#include <GfxMgr.h>
#include <InputMgr.h>
#include <Types381.h>

#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreMeshManager.h>

GameMgr::GameMgr(Engine *engine) :
	Mgr(engine) {
	cameraNode = 0;
}

GameMgr::~GameMgr() {

}

void GameMgr::Init(void) {

}

void GameMgr::LoadLevel(void) {
	engine->gfxMgr->mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	engine->gfxMgr->mCamera->lookAt(Ogre::Vector3(0, 0, 0));
	Ogre::Light* light = engine->gfxMgr->mSceneMgr->createLight("MainLight");
	light->setPosition(20.0, 80.0, 50.0);

#if 0
	Ogre::Entity* ogreEntityFixed = engine->gfxMgr->mSceneMgr->createEntity("robot.mesh");
	Ogre::SceneNode* sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 100, -200));
	sceneNode->attachObject(ogreEntityFixed);
	//sceneNode->showBoundingBox(true);
#endif

	// A node to attach the camera to so we can move the camera node instead of the camera.
	cameraNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	cameraNode->setPosition(0, 200, 500);
	cameraNode->attachObject(engine->gfxMgr->mCamera);
	engine->inputMgr->cameraNode = cameraNode;

	MakeGround();
	MakeSky();
	MakeEntities();
}

void GameMgr::Tick(float dt) {
}

void GameMgr::Stop(void) {

}

void GameMgr::MakeEntities() {
	float change_x_per_object;

	//create 3 carriers
	change_x_per_object = 700.f;
	for (unsigned int i = 0; i < 3; ++i)
		engine->entityMgr->CreateEntityOfTypeAtPosition(CarrierType, Ogre::Vector3(i * change_x_per_object, 0, -1000.f));

	//create 4 frigates
	change_x_per_object = 450.f;
	for (unsigned int i = 0; i < 4; ++i)
		engine->entityMgr->CreateEntityOfTypeAtPosition(FrigateType, Ogre::Vector3(i * change_x_per_object, 0, -800.f));

	//create 5 destroyers
	change_x_per_object = 250.f;
	for (unsigned int i = 0; i < 5; ++i)
		engine->entityMgr->CreateEntityOfTypeAtPosition(DDG51Type, Ogre::Vector3(i * change_x_per_object, 0, -600.f));

	//create 6 speedboats
	change_x_per_object = 200.f;
	for (unsigned int i = 0; i < 6; ++i)
		engine->entityMgr->CreateEntityOfTypeAtPosition(SpeedBoatType, Ogre::Vector3(i * change_x_per_object, 0, -425.f));

	//create 4 alienships
	change_x_per_object = 250.f;
	for (unsigned int i = 0; i < 4; ++i)
		engine->entityMgr->CreateEntityOfTypeAtPosition(AlienType, Ogre::Vector3(i * change_x_per_object, 0, -250.f));

	//create 2 banshee
	change_x_per_object = 150.f;
	for (unsigned int i = 0; i < 2; ++i)
		engine->entityMgr->CreateEntityOfTypeAtPosition(BansheeType, Ogre::Vector3(i * change_x_per_object, 0, -100.f));

	engine->entityMgr->SelectNextEntity(); //sets selection
}

void GameMgr::MakeGround() {
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 15000, 15000, 20, 20,
		true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	Ogre::Entity* groundEntity = engine->gfxMgr->mSceneMgr->createEntity("ground");
	Ogre::SceneNode* groundNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode("ground");
	groundNode->attachObject(groundEntity);
	groundEntity->setCastShadows(false);
	//groundEntity->setMaterialName("Ocean2_HLSL_GLSL");
	groundEntity->setMaterialName("OceanHLSL_GLSL");
	//groundEntity->setMaterialName("Ocean2_Cg");
	//groundEntity->setMaterialName("NavyCg");
}

void GameMgr::MakeSky() {
	engine->gfxMgr->mSceneMgr->setSkyBox(true, "Examples/MorningSkyBox");
}
