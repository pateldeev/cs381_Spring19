#include "GameMgr.h"

#include "Engine.h"
#include "GfxMgr.h"
#include "InputMgr.h"
#include "EntityMgr.h"

#include <OgreEntity.h>
#include <OgreMeshManager.h>
#include <OgreRenderWindow.h>

GameMgr::GameMgr(Engine *engine) :
	Mgr(engine), m_graphics_scene_manager(nullptr), m_entity_mgr(nullptr), m_ocean_height(0), m_camera_controller(nullptr),
	m_velocity_update_cooldown(0), m_ray_query(nullptr) {
}

GameMgr::~GameMgr(void) {

}

void GameMgr::Init(void) {
	m_entity_mgr = m_engine->m_entity_mgr;
}

void GameMgr::LoadLevel(void) {
	m_graphics_scene_manager = m_engine->m_gfx_mgr->GetOgreSceneManger();
	m_ray_query = m_graphics_scene_manager->createRayQuery(Ogre::Ray());
	SetupCameraController();
	SetupSky();
	SetupOcean();
	SetupShips();
}

void GameMgr::Tick(float dt) {
	m_camera_controller->Tick(dt);
	UpdateSelectedEntities(dt);
}

void GameMgr::Stop(void) {

}

void GameMgr::InjectKeyDown(const OIS::KeyEvent &key_down) {
	m_camera_controller->InjectKeyDown(key_down); //move camera as needed

	if (key_down.key == OIS::KC_TAB) { //change selected entity
		m_entity_mgr->ClearGroup();
		if (m_engine->m_input_mgr->IsKeyPressed(OIS::KC_LSHIFT))
			m_entity_mgr->SelectPreviousEntity();
		else
			m_entity_mgr->SelectNextEntity();
	}

	if (key_down.key == OIS::KC_SPACE && m_entity_mgr->ResetSelectedSpeedAndHeading()) {
		m_entity_mgr->ResetGroupSpeedAndHeading();
		std::cout << "Selected Ships movement and heading reset! It make take a while for ships to stop and orient correctly!" << std::endl;
	}

	if (key_down.key == OIS::KC_RIGHT || key_down.key == OIS::KC_LEFT || key_down.key == OIS::KC_UP || key_down.key == OIS::KC_DOWN)
		m_velocity_update_cooldown = 0.001;

	if (key_down.key == OIS::KC_EQUALS)
		m_entity_mgr->ChangeSelectedDesiredHeight(8.f);
	else if (key_down.key == OIS::KC_MINUS)
		m_entity_mgr->ChangeSelectedDesiredHeight(-8.f);

	if (key_down.key == OIS::KC_T) {
		if (m_camera_controller->IsFollowingEntity())
			m_camera_controller->StopFollowingEntity();
		else
			m_camera_controller->FollowEntity(m_entity_mgr->GetSelectedEntity());
	}
}

void GameMgr::InjectKeyUp(const OIS::KeyEvent &key_up) {
	m_camera_controller->InjectKeyUp(key_up); //stop camera movement as needed
}

void GameMgr::InjectMouseClick(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
//execute ray cast to find entity being clicked on
	m_ray_query->setRay(
		m_engine->m_gfx_mgr->GetOgreCamera()->getCameraToViewportRay(
			float(arg.state.X.abs) / float(m_engine->m_gfx_mgr->GetOrgreRenderWindow()->getWidth()),
			float(arg.state.Y.abs) / float(m_engine->m_gfx_mgr->GetOrgreRenderWindow()->getHeight())));

	m_ray_query->setSortByDistance(true);

	Ogre::RaySceneQueryResult &result = m_ray_query->execute();
	for (Ogre::RaySceneQueryResult::iterator result_iter = result.begin(); result_iter != result.end(); ++result_iter) {
		if (result_iter->movable) {
			std::string hit_entity_name = result_iter->movable->getParentSceneNode()->getName();

			if (hit_entity_name != "" && hit_entity_name != "camera" && hit_entity_name != "ocean") {
				if (id == OIS::MouseButtonID::MB_Left) {
					m_entity_mgr->ClearGroup();
					m_entity_mgr->SelectEntityByName(hit_entity_name);
				} else if (id == OIS::MouseButtonID::MB_Right) {
					m_entity_mgr->AddEntityToGroup(hit_entity_name);
				}
			}
		}
	}
}

void GameMgr::SetupCameraController(void) {
	m_camera_controller = new CameraController(m_engine->m_gfx_mgr->GetOgreCamera(), m_graphics_scene_manager,
		Ogre::Vector3(0.f, m_ocean_height + 200.f, 0.f));
	m_camera_controller->SetMinimumY(m_ocean_height + 2);
}

void GameMgr::SetupSky(void) {
	m_graphics_scene_manager->setSkyBox(true, "Examples/MorningSkyBox");
}

void GameMgr::SetupOcean(void) {
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("ocean", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 10000, 10000, 20, 20, true,
		1, 5, 5, Ogre::Vector3::UNIT_Z);

	Ogre::SceneNode *ocean_node = m_graphics_scene_manager->getRootSceneNode()->createChildSceneNode("ocean");
	Ogre::Entity *ocean_entity = m_graphics_scene_manager->createEntity("ocean");
	ocean_node->attachObject(ocean_entity);

	ocean_entity->setCastShadows(false);
	ocean_entity->setMaterialName("OceanHLSL_GLSL");
	ocean_node->translate(Ogre::Vector3(0.f, m_ocean_height, 0.f));
}

void GameMgr::SetupShips(void) {
	float change_x_per_object;

//create 2 carriers
	change_x_per_object = 700.f;
	for (unsigned int i = 0; i < 2; ++i)
		m_entity_mgr->CreateEntityOfTypeAtPosition(EntityType::CARRIER, Ogre::Vector3(i * change_x_per_object, m_ocean_height, -1400.f));

//create 4 frigates
	change_x_per_object = 450.f;
	for (unsigned int i = 0; i < 4; ++i)
		m_entity_mgr->CreateEntityOfTypeAtPosition(EntityType::FRIGATE, Ogre::Vector3(i * change_x_per_object, m_ocean_height, -1200.f));

//create 5 destroyers
	change_x_per_object = 250.f;
	for (unsigned int i = 0; i < 5; ++i)
		m_entity_mgr->CreateEntityOfTypeAtPosition(EntityType::DESTROYER, Ogre::Vector3(i * change_x_per_object, m_ocean_height, -1000.f));

//create 6 speedboats
	change_x_per_object = 200.f;
	for (unsigned int i = 0; i < 6; ++i)
		m_entity_mgr->CreateEntityOfTypeAtPosition(EntityType::SPEEDBOAT, Ogre::Vector3(i * change_x_per_object, m_ocean_height, -825.f));

//create 4 alienships
	change_x_per_object = 250.f;
	for (unsigned int i = 0; i < 4; ++i)
		m_entity_mgr->CreateEntityOfTypeAtPosition(EntityType::ALIEN, Ogre::Vector3(i * change_x_per_object, m_ocean_height, -650.f));
}

void GameMgr::UpdateSelectedEntities(float dt) {
	if (m_velocity_update_cooldown > 0) {
		m_velocity_update_cooldown -= dt;

		if (m_velocity_update_cooldown <= 0) {
			const float velocity_change = 25.f;
			const float heading_change = 20.f;

			if (m_engine->m_input_mgr->IsKeyPressed(OIS::KC_RIGHT)) {
				m_entity_mgr->ChangeSelectedDesiredHeading(-heading_change);
				m_entity_mgr->ChangeGroupDesiredHeading(-heading_change);
			} else if (m_engine->m_input_mgr->IsKeyPressed(OIS::KC_LEFT)) {
				m_entity_mgr->ChangeSelectedDesiredHeading(heading_change);
				m_entity_mgr->ChangeGroupDesiredHeading(heading_change);
			} else if (m_engine->m_input_mgr->IsKeyPressed(OIS::KC_UP)) {
				m_entity_mgr->ChangeSelectedDesiredSpeed(velocity_change);
				m_entity_mgr->ChangeGroupDesiredSpeed(velocity_change);
			} else if (m_engine->m_input_mgr->IsKeyPressed(OIS::KC_DOWN)) {
				m_entity_mgr->ChangeSelectedDesiredSpeed(-velocity_change);
				m_entity_mgr->ChangeGroupDesiredSpeed(-velocity_change);
			} else
				return; //no key pressed. Do not update cooldown

			m_entity_mgr->DisplaySelectedSpeedAndHeading();

			m_velocity_update_cooldown += 0.5; //wait before updating again
		}
	}
}
