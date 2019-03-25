#ifndef GFXMGR_H_
#define GFXMGR_H_

#include <OGRE/OgreRoot.h>
#include <OGRE/OgreWindowEventUtilities.h>

#include <Mgr.h>

class GfxMgr: public Mgr, public Ogre::WindowEventListener, public Ogre::FrameListener {
public:
	GfxMgr(Engine *engine);
	virtual ~GfxMgr();

	virtual void windowClosed(Ogre::RenderWindow* rw);
	virtual void windowResized(Ogre::RenderWindow* rw);
//---------------
	void Init();
	void LoadLevel();
	void Tick(float dt);
	void Stop();

	//Ogre related stuff
	Ogre::Root* mRoot;
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;
	Ogre::RenderWindow* mWindow;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;

};

#endif /* GFXMGR_H_ */
