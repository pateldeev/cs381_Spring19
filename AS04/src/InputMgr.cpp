#include "InputMgr.h"

#include "Engine.h"
#include "GfxMgr.h"
#include "GameMgr.h"

#include <OgreRenderWindow.h>

InputMgr::InputMgr(Engine *engine) :
	Mgr(engine), m_graphics_window(nullptr), m_input_manager(nullptr), m_keyboard(nullptr), m_mouse(nullptr) {
}

InputMgr::~InputMgr(void) {

}

void InputMgr::Init(void) {
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	m_graphics_window = m_engine->m_gfx_mgr->GetOrgreRenderWindow();
	std::size_t window_handle = 0;
	std::ostringstream window_handle_str;
	m_graphics_window->getCustomAttribute("WINDOW", &window_handle);
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

	Ogre::LogManager::getSingletonPtr()->logMessage("*** OIS Initialized ***");
}

void InputMgr::LoadLevel(void) {
	m_keyboard = static_cast<OIS::Keyboard*>(m_input_manager->createInputObject(OIS::OISKeyboard, true));
	m_mouse = static_cast<OIS::Mouse*>(m_input_manager->createInputObject(OIS::OISMouse, true));

	m_keyboard->setEventCallback(this);
	m_mouse->setEventCallback(this);

	windowResized(m_graphics_window);
	Ogre::WindowEventUtilities::addWindowEventListener(m_graphics_window, this);
}

void InputMgr::Tick(float dt) {
	m_keyboard->capture();
	m_mouse->capture();
	if (m_keyboard->isKeyDown(OIS::KeyCode::KC_Q) || m_keyboard->isKeyDown(OIS::KeyCode::KC_ESCAPE)) //exit when pressing Q or ESC
		m_engine->m_keep_running = false;
}

void InputMgr::Stop(void) {
	windowClosed(m_graphics_window);
}

bool InputMgr::IsKeyPressed(const OIS::KeyCode &key) const {
	return m_keyboard->isKeyDown(key);
}

bool InputMgr::keyPressed(const OIS::KeyEvent &arg) {
	m_engine->m_game_mgr->InjectKeyDown(arg); //let game manager handle input
	return true;
}

bool InputMgr::keyReleased(const OIS::KeyEvent &arg) {
	m_engine->m_game_mgr->InjectKeyUp(arg); //let game manager handle input
	return true;
}

bool InputMgr::mouseMoved(const OIS::MouseEvent &arg) {
	return true;
}

bool InputMgr::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
	m_engine->m_game_mgr->InjectMouseClick(arg, id);
	return true;
}

bool InputMgr::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
	return true;
}

void InputMgr::windowResized(Ogre::RenderWindow *rw) {
	int left, top;
	unsigned int width, height, depth;

	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState& ms = m_mouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void InputMgr::windowClosed(Ogre::RenderWindow *rw) {
	if (rw == m_graphics_window) {
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
