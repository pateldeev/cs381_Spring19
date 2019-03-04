/*
 -----------------------------------------------------------------------------
 Filename: AS03.cpp
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains implementation of AS03 class
 */

#include "AS03.h"

#include <OgreEntity.h>
#include <OgreSubEntity.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreException.h>
#include <OgreMeshManager.h>

AS03::AS03(const std::string &window_name, int surface_height) :
	m_window_name(window_name), m_root(nullptr), m_resources_cfg("resources.cfg"), m_plugins_cfg("plugins.cfg"), m_window(nullptr),
	m_scene_manager(nullptr), m_camera(nullptr), m_input_manager(nullptr), m_keyboard(nullptr), m_mouse(nullptr), m_ocean_height(surface_height),
	m_camera_controller(nullptr), m_velocity_update_cooldown(0), m_entity_manager(nullptr), m_ray_query(nullptr) {

}

AS03::~AS03(void) {
	delete m_camera_controller;
	delete m_entity_manager;

	windowClosed(m_window);

	delete m_root;
}

bool AS03::go(void) {
	m_root = new Ogre::Root(m_plugins_cfg);

	setupResources();

	if (!(m_root->restoreConfig() || m_root->showConfigDialog()))
		return false;

	m_window = m_root->initialise(true, m_window_name);

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	setupScene();

	setupOIS();

	m_root->addFrameListener(this);

	m_root->startRendering();

	return true;
}

void AS03::setupResources(void) {
	Ogre::ConfigFile cf;
	cf.load(m_resources_cfg); // Load resource paths from config file

	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator sec_iter = cf.getSectionIterator();
	while (sec_iter.hasMoreElements()) {
		Ogre::String sec_name = sec_iter.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = sec_iter.getNext();

		for (Ogre::ConfigFile::SettingsMultiMap::iterator settings_iter = settings->begin(); settings_iter != settings->end(); ++settings_iter)
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(settings_iter->second, settings_iter->first, sec_name);
	}
}

void AS03::setupScene(void) {
	m_scene_manager = m_root->createSceneManager(Ogre::ST_GENERIC);
	setupCamera();
	setupLighting();
	setupOcean();
	setupSky();
	setupEntities();
	m_ray_query = m_scene_manager->createRayQuery(Ogre::Ray());
}

void AS03::setupOIS(void) {
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	std::size_t window_handle = 0;
	std::ostringstream window_handle_str;
	m_window->getCustomAttribute("WINDOW", &window_handle);
	window_handle_str << window_handle;

	OIS::ParamList pl;
	pl.insert(std::make_pair(std::string("WINDOW"), window_handle_str.str()));
#if defined OIS_WIN32_PLATFORM
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
	pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
	pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
	pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
	pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
	pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif
	m_input_manager = OIS::InputManager::createInputSystem(pl);

	m_keyboard = static_cast<OIS::Keyboard*>(m_input_manager->createInputObject(OIS::OISKeyboard, true));
	m_mouse = static_cast<OIS::Mouse*>(m_input_manager->createInputObject(OIS::OISMouse, true));

	m_keyboard->setEventCallback(this);
	m_mouse->setEventCallback(this);

	windowResized(m_window);
	Ogre::WindowEventUtilities::addWindowEventListener(m_window, this);

	Ogre::LogManager::getSingletonPtr()->logMessage("*** OIS Initialized ***");
}

void AS03::setupCamera(void) {
	m_camera = m_scene_manager->createCamera("camera");
	m_camera->setPosition(Ogre::Vector3(0.f));
	m_camera->lookAt(0, 0, -300);
	m_camera->setNearClipDistance(5);

	Ogre::Viewport* vp = m_window->addViewport(m_camera);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	m_camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

	m_camera_controller = new CameraController(m_camera, m_scene_manager, Ogre::Vector3(0.f, m_ocean_height + 200.f, 0.f));
	m_camera_controller->setMinimumY(m_ocean_height + 2);
}

void AS03::setupLighting(void) {
	m_scene_manager->setAmbientLight(Ogre::ColourValue(0.8, 0.8, 0.8));
	m_scene_manager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
}

void AS03::setupOcean(void) {
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("ocean", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 10000, 10000, 20, 20, true,
		1, 5, 5, Ogre::Vector3::UNIT_Z);

	Ogre::SceneNode *ocean_node = m_scene_manager->getRootSceneNode()->createChildSceneNode("ocean");
	Ogre::Entity *ocean_entity = m_scene_manager->createEntity("ocean");
	ocean_node->attachObject(ocean_entity);

	ocean_entity->setCastShadows(false);
	ocean_entity->setMaterialName("OceanHLSL_GLSL");
	ocean_node->translate(Ogre::Vector3(0.f, m_ocean_height, 0.f));

	addIsland(Ogre::Vector3(0,m_ocean_height - 30, -2500), "island[0]");
	addIsland(Ogre::Vector3(2000,m_ocean_height - 45, -3000), "island[1]");
	addIsland(Ogre::Vector3(-1000,m_ocean_height  - 25, -1000), "island[2]");

}

void AS03::addIsland(const Ogre::Vector3 &location, const std::string &name) {
	Ogre::Entity *island = m_scene_manager->createEntity("geosphere4500.mesh");
	Ogre::MaterialPtr island_mat = island->getSubEntity(0)->getMaterial()->clone(name + "_mat");
	island_mat->setAmbient(0, 1, 0);
	island_mat->setDiffuse(1, 0, 0, 0);
	island->setMaterialName(island_mat->getName());

	Ogre::SceneNode *island_node = m_scene_manager->getRootSceneNode()->createChildSceneNode(name, location);
	island_node->attachObject(island);
}

void AS03::setupSky(void) {
	m_scene_manager->setSkyBox(true, "Examples/MorningSkyBox");
}

void AS03::setupEntities(void) {
	m_entity_manager = new EntityMgr(m_scene_manager);

	float change_x_per_object;

	//create 2 carriers
	change_x_per_object = 700.f;
	for (unsigned int i = 0; i < 2; ++i)
		m_entity_manager->CreateEntityOfTypeAtPosition(EntityType::CARRIER, Ogre::Vector3(i * change_x_per_object, m_ocean_height, -1400.f));

	//create 4 frigates
	change_x_per_object = 450.f;
	for (unsigned int i = 0; i < 4; ++i)
		m_entity_manager->CreateEntityOfTypeAtPosition(EntityType::FRIGATE, Ogre::Vector3(i * change_x_per_object, m_ocean_height, -1200.f));

	//create 5 destroyers
	change_x_per_object = 250.f;
	for (unsigned int i = 0; i < 5; ++i)
		m_entity_manager->CreateEntityOfTypeAtPosition(EntityType::DESTROYER, Ogre::Vector3(i * change_x_per_object, m_ocean_height, -1000.f));

	//create 6 speedboats
	change_x_per_object = 200.f;
	for (unsigned int i = 0; i < 6; ++i)
		m_entity_manager->CreateEntityOfTypeAtPosition(EntityType::SPEEDBOAT, Ogre::Vector3(i * change_x_per_object, m_ocean_height, -825.f));

	//create 4 alienships
	change_x_per_object = 250.f;
	for (unsigned int i = 0; i < 4; ++i)
		m_entity_manager->CreateEntityOfTypeAtPosition(EntityType::ALIEN, Ogre::Vector3(i * change_x_per_object, m_ocean_height, -650.f));

}

void AS03::windowResized(Ogre::RenderWindow *rw) {
	int left, top;
	unsigned int width, height, depth;

	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState& ms = m_mouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void AS03::windowClosed(Ogre::RenderWindow *rw) {
	if (rw == m_window) {
		if (m_input_manager) {
			m_input_manager->destroyInputObject(m_mouse);
			m_input_manager->destroyInputObject(m_keyboard);

			OIS::InputManager::destroyInputSystem(m_input_manager);
			m_input_manager = nullptr;
			m_keyboard = nullptr;
			m_mouse = nullptr;
		}
	}
}

bool AS03::keyPressed(const OIS::KeyEvent &arg) {
	m_camera_controller->injectKeyDown(arg); //move camera as needed

	if (arg.key == OIS::KC_TAB) { //change selected entity
		m_entity_manager->clearGroup();
		if (m_keyboard->isKeyDown(OIS::KC_LSHIFT))
			m_entity_manager->selectPreviousEntity();
		else
			m_entity_manager->selectNextEntity();
	}

	if (arg.key == OIS::KC_SPACE && m_entity_manager->resetSelectedSpeedAndHeading()) {
		m_entity_manager->resetGroupSpeedAndHeading();
		std::cout << "Selected Ships movement and heading reset! It make take a while for ships to stop and orient correctly!" << std::endl;
	}

	if (arg.key == OIS::KC_RIGHT || arg.key == OIS::KC_LEFT || arg.key == OIS::KC_UP || arg.key == OIS::KC_DOWN)
		m_velocity_update_cooldown = 0.001;

	return true;
}

bool AS03::keyReleased(const OIS::KeyEvent &arg) {
	m_camera_controller->injectKeyUp(arg); //stop camera movement as needed
	return true;
}

bool AS03::mouseMoved(const OIS::MouseEvent &arg) {
	return true;
}

bool AS03::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
	//execute ray cast to find entity being clicked on
	m_ray_query->setRay(
		m_camera->getCameraToViewportRay(float(arg.state.X.abs) / float(m_window->getWidth()),
			float(arg.state.Y.abs) / float(m_window->getHeight())));
	m_ray_query->setSortByDistance(true);

	Ogre::RaySceneQueryResult &result = m_ray_query->execute();
	for (Ogre::RaySceneQueryResult::iterator result_iter = result.begin(); result_iter != result.end(); ++result_iter) {
		if (result_iter->movable) {
			std::string hit_entity_name = result_iter->movable->getParentSceneNode()->getName();

			if (hit_entity_name != "" && hit_entity_name != "camera" && hit_entity_name != "ocean") {
				if (id == OIS::MouseButtonID::MB_Left) {
					m_entity_manager->clearGroup();
					m_entity_manager->selectEntityByName(hit_entity_name);
				} else if (id == OIS::MouseButtonID::MB_Right) {
					m_entity_manager->addEntityToGroup(hit_entity_name);
				}
			}
		}
	}
	return true;
}

bool AS03::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
	return true;
}

bool AS03::frameRenderingQueued(const Ogre::FrameEvent &e) {
	if (m_window->isClosed())
		return false;

	m_keyboard->capture();
	m_mouse->capture();

	if (!processUnbufferedInput(e))
		return false;

	return true;
}

bool AS03::processUnbufferedInput(const Ogre::FrameEvent &e) {
	if (m_keyboard->isKeyDown(OIS::KeyCode::KC_Q) || m_keyboard->isKeyDown(OIS::KeyCode::KC_ESCAPE)) //exit when pressing Q or ESC
		return false;

	updateVelocity(e.timeSinceLastEvent); //update velocity of selected object if needed
	m_camera_controller->Tick(e.timeSinceLastEvent); //update camera
	m_entity_manager->Tick(e.timeSinceLastEvent); //update entities

	return true;
}

void AS03::updateVelocity(float dt) {
	if (m_velocity_update_cooldown > 0) {
		m_velocity_update_cooldown -= dt;

		if (m_velocity_update_cooldown <= 0) {
			const float velocity_change = 25.f;
			const float heading_change = 20.f;

			if (m_keyboard->isKeyDown(OIS::KC_RIGHT)) {
				m_entity_manager->changeSelectedDesiredHeading(-heading_change);
				m_entity_manager->changeGroupDesiredHeading(-heading_change);
			} else if (m_keyboard->isKeyDown(OIS::KC_LEFT)) {
				m_entity_manager->changeSelectedDesiredHeading(heading_change);
				m_entity_manager->changeGroupDesiredHeading(heading_change);
			} else if (m_keyboard->isKeyDown(OIS::KC_UP)) {
				m_entity_manager->changeSelectedDesiredSpeed(velocity_change);
				m_entity_manager->changeGroupDesiredSpeed(velocity_change);
			} else if (m_keyboard->isKeyDown(OIS::KC_DOWN)) {
				m_entity_manager->changeSelectedDesiredSpeed(-velocity_change);
				m_entity_manager->changeGroupDesiredSpeed(-velocity_change);
			} else
				return; //no key pressed. Do not update cooldown

			m_entity_manager->displaySelectedSpeedAndHeading();

			m_velocity_update_cooldown += 0.5; //wait before updating again
		}
	}

}
