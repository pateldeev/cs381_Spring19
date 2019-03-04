/*
 -----------------------------------------------------------------------------
 Filename: TutorialApplication.cpp
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains implementation of TutorialApplication class
 */

#include "TutorialApplication.h"

TutorialApplication::TutorialApplication(const std::string &windowName, int surface_height) :
	BaseApplication(windowName), m_camera_controller(nullptr), m_entity_manager(nullptr), m_ocean_height(surface_height),
	m_velocity_update_cooldown(0) {
}

TutorialApplication::~TutorialApplication(void) {
	delete m_camera_controller;
	delete m_entity_manager;
}

void TutorialApplication::createScene(void) {
	setupLighting();

	setupCamera();

	setupGround();

	setupSky();

	m_entity_manager = new EntityMgr(mSceneMgr);

	float change_x_per_object;

	//create 5 spheres
	change_x_per_object = 250.f;
	for (unsigned int i = 0; i < 5; ++i)
		m_entity_manager->CreateEntityOfTypeAtPosition(EntityType::SPHERE, Ogre::Vector3(i * change_x_per_object, m_ocean_height, -1000.f));

	//create 5 cubes
	change_x_per_object = 175.f;
	for (unsigned int i = 0; i < 5; ++i)
		m_entity_manager->CreateEntityOfTypeAtPosition(EntityType::CUBE, Ogre::Vector3(i * change_x_per_object, m_ocean_height, -600.f));

}

bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent &e) {
	if (!processUnbufferedInput(e))
		return false;

	return BaseApplication::frameRenderingQueued(e);
}

bool TutorialApplication::keyPressed(const OIS::KeyEvent &arg) {
	m_camera_controller->injectKeyDown(arg); //move camera as needed

	if (arg.key == OIS::KC_TAB) //change selected entity
		m_entity_manager->selectNextEntity();

	if (arg.key == OIS::KC_SPACE) //stop selected object
		m_entity_manager->setSelectedEntityVelocity(Ogre::Vector3(0.f), false);

	if (arg.key == OIS::KC_RIGHT || arg.key == OIS::KC_LEFT || arg.key == OIS::KC_UP || arg.key == OIS::KC_DOWN || arg.key == OIS::KC_PGUP
		|| arg.key == OIS::KC_PGDOWN)
		m_velocity_update_cooldown = 0.001;

	return BaseApplication::keyPressed(arg);
}

bool TutorialApplication::keyReleased(const OIS::KeyEvent &arg) {
	m_camera_controller->injectKeyUp(arg); //stop camera movement as needed

	return BaseApplication::keyReleased(arg);
}

bool TutorialApplication::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
	return BaseApplication::mousePressed(arg, id);
}

bool TutorialApplication::processUnbufferedInput(const Ogre::FrameEvent &e) {
	if (mKeyboard->isKeyDown(OIS::KeyCode::KC_Q) || mKeyboard->isKeyDown(OIS::KeyCode::KC_ESCAPE)) //exit when pressing Q or ESC
		return false;

	updateVelocity(e.timeSinceLastEvent); //update velocity of selected object if needed

	m_camera_controller->Tick(e.timeSinceLastEvent); //update camera

	m_entity_manager->Tick(e.timeSinceLastEvent); //update entities

	return true;
}

void TutorialApplication::setupLighting(void) {
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.8, 0.8, 0.8));
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
}

void TutorialApplication::setupCamera(void) {
	m_camera_controller = new CameraController(mCamera, mSceneMgr, Ogre::Vector3(0.f, m_ocean_height + 200.f, 0.f));
	m_camera_controller->setMinimumY(m_ocean_height + 2);
}

void TutorialApplication::setupGround(void) {
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("ocean", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 10000, 10000, 20, 20, true,
		1, 5, 5, Ogre::Vector3::UNIT_Z);

	Ogre::SceneNode *ocean_node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity *ocean_entity = mSceneMgr->createEntity("ocean");
	ocean_node->attachObject(ocean_entity);

	ocean_entity->setCastShadows(false);
	ocean_entity->setMaterialName("OceanHLSL_GLSL");
	ocean_node->translate(Ogre::Vector3(0.f, m_ocean_height, 0.f));
}

void TutorialApplication::setupSky(void) {
	mSceneMgr->setSkyBox(true, "Examples/MorningSkyBox");
}

void TutorialApplication::updateVelocity(float dt) {
	if (m_velocity_update_cooldown > 0) {
		m_velocity_update_cooldown -= dt;

		if (m_velocity_update_cooldown <= 0) {
			const float velocity_change = 30.f;

			if (mKeyboard->isKeyDown(OIS::KC_RIGHT))
				m_entity_manager->setSelectedEntityVelocity(Ogre::Vector3(velocity_change, 0.f, 0.f));
			else if (mKeyboard->isKeyDown(OIS::KC_LEFT))
				m_entity_manager->setSelectedEntityVelocity(Ogre::Vector3(-velocity_change, 0.f, 0.f));
			else if (mKeyboard->isKeyDown(OIS::KC_UP))
				m_entity_manager->setSelectedEntityVelocity(Ogre::Vector3(0.f, 0.f, -velocity_change));
			else if (mKeyboard->isKeyDown(OIS::KC_DOWN))
				m_entity_manager->setSelectedEntityVelocity(Ogre::Vector3(0.f, 0.f, velocity_change));
			else if (mKeyboard->isKeyDown(OIS::KC_PGUP))
				m_entity_manager->setSelectedEntityVelocity(Ogre::Vector3(0.f, velocity_change, 0.f));
			else if (mKeyboard->isKeyDown(OIS::KC_PGDOWN))
				m_entity_manager->setSelectedEntityVelocity(Ogre::Vector3(0.f, -velocity_change, 0.f));
			else
				return; //no key pressed. Do not update cooldown

			m_velocity_update_cooldown += 1; //wait before updating again
		}
	}

}
