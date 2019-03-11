#ifndef INPUTMGR_H_
#define INPUTMGR_H_

#include "Mgr.h"

#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

class InputMgr: public Mgr, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener {

public:
	InputMgr(Engine *engine);
	virtual ~InputMgr(void);

public:
	virtual void Init(void) override final;
	virtual void LoadLevel(void) override final;
	virtual void Tick(float dt) override final;
	virtual void Stop(void) override final;

public:
	bool IsKeyPressed(const OIS::KeyCode &key) const;

private:
	virtual bool keyPressed(const OIS::KeyEvent &arg) override final;
	virtual bool keyReleased(const OIS::KeyEvent &arg) override final;

	virtual bool mouseMoved(const OIS::MouseEvent &arg) override final;
	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) override final;
	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) override final;

	virtual void windowResized(Ogre::RenderWindow *rw) override final;
	virtual void windowClosed(Ogre::RenderWindow *rw) override final;

private:
	Ogre::RenderWindow *m_graphics_window;

	OIS::InputManager *m_input_manager;
	OIS::Keyboard *m_keyboard;
	OIS::Mouse *m_mouse;
};

#endif
