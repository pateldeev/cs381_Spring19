#include "GfxMgr.h"

#include "Engine.h"

#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>

#include <assert.h>

GfxMgr::GfxMgr(Engine *engine) :
	Mgr(engine), m_window_name("Main_Window"), m_root(nullptr), m_resources_cfg("resources.cfg"), m_plugins_cfg("plugins.cfg"), m_window(nullptr),
	m_scene_manager(nullptr), m_camera(nullptr) {
}

GfxMgr::~GfxMgr(void) {
}

void GfxMgr::Init(void) {
	m_root = new Ogre::Root(m_plugins_cfg);

	SetupOgreResources();

	assert(m_root->restoreConfig() || m_root->showConfigDialog());

	m_window = m_root->initialise(true, m_window_name);

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	m_scene_manager = m_root->createSceneManager(Ogre::ST_GENERIC);
}

void GfxMgr::LoadLevel(void) {
	SetupOgreScene();
}

void GfxMgr::Tick(float dt) {
	if (m_window->isClosed() || !m_root->renderOneFrame()) //Render frame to orge. Shutdown if it fails
		m_engine->m_keep_running = false;
}

void GfxMgr::Stop(void) {
	delete m_root;
	m_root = nullptr;
}

Ogre::RenderWindow* GfxMgr::GetOrgreRenderWindow(void) {
	return m_window;
}

Ogre::SceneManager* GfxMgr::GetOgreSceneManger(void) {
	return m_scene_manager;
}

Ogre::Camera* GfxMgr::GetOgreCamera(void) {
	return m_camera;
}

void GfxMgr::SetupOgreResources(void) {
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

void GfxMgr::SetupOgreScene(void) {
	SetupOgreCamera();
	SetupOgreLighting();
}

void GfxMgr::SetupOgreCamera(void) {
	m_camera = m_scene_manager->createCamera("camera");
	m_camera->setPosition(Ogre::Vector3(0.f));
	m_camera->lookAt(0, 0, -300);
	m_camera->setNearClipDistance(5);

	Ogre::Viewport *vp = m_window->addViewport(m_camera);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	m_camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

void GfxMgr::SetupOgreLighting(void) {
	m_scene_manager->setAmbientLight(Ogre::ColourValue(0.8, 0.8, 0.8));
	m_scene_manager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
}
