#ifndef INPUTMGR_H_
#define INPUTMGR_H_

#include <ois/OISEvents.h>
#include <ois/OISInputManager.h>
#include <ois/OISKeyboard.h>
#include <ois/OISMouse.h>

#include <OGRE/OgreSceneNode.h>

#include <Mgr.h>

class Engine;
class Entity381;

class InputMgr: public Mgr, public OIS::KeyListener, public OIS::MouseListener {

public:
	InputMgr(Engine *engine);
	virtual ~InputMgr();

	virtual bool keyPressed(const OIS::KeyEvent& ke);
	virtual bool keyReleased(const OIS::KeyEvent& ke);

	virtual bool mouseMoved(const OIS::MouseEvent& me);
	virtual bool mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id);

	OIS::InputManager* mInputMgr;
	OIS::Keyboard* mKeyboard;
	OIS::Mouse* mMouse;

	void Init();
	void Stop();
	void Tick(float dt);
	void LoadLevel();

	float keyboardTimer;
	float deltaDesiredSpeed, deltaDesiredHeading, deltaDesiredAltitude;
	void UpdateCamera(float dt);
	void UpdateVelocityAndSelection(float dt);

	Ogre::SceneNode *cameraNode;
	Entity381 *cameraFollowing;
};

#endif /* INPUTMGR_H_ */
