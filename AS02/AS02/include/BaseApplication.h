/*
 -----------------------------------------------------------------------------
 Filename:    BaseApplication.h
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

#ifndef __BaseApplication_h_
#define __BaseApplication_h_

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>


#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>

#ifdef OGRE_STATIC_LIB
#  define OGRE_STATIC_GL
#  if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#    define OGRE_STATIC_Direct3D9
// D3D10 will only work on vista, so be careful about statically linking
#    if OGRE_USE_D3D10
#      define OGRE_STATIC_Direct3D10
#    endif
#  endif

#  define OGRE_STATIC_BSPSceneManager
#  define OGRE_STATIC_ParticleFX
#  define OGRE_STATIC_CgProgramManager

#  ifdef OGRE_USE_PCZ
#    define OGRE_STATIC_PCZSceneManager
#    define OGRE_STATIC_OctreeZone
#  else
#    define OGRE_STATIC_OctreeSceneManager
#  endif
#  include "OgreStaticPluginLoader.h"
#endif

//---------------------------------------------------------------------------

class BaseApplication: public Ogre::FrameListener,
	public Ogre::WindowEventListener,
	public OIS::KeyListener,
	public OIS::MouseListener,
	OgreBites::SdkTrayListener {

public:
	BaseApplication(const std::string &window_name);
	virtual ~BaseApplication(void);

	virtual void go(void);

protected:
	virtual bool setup(void);
	virtual bool configure(void);
	virtual void chooseSceneManager(void);
	virtual void createCamera(void);
	virtual void createFrameListener(void);
	virtual void createScene(void) = 0;
	virtual void destroyScene(void);
	virtual void createViewports(void);
	virtual void setupResources(void);
	virtual void createResourceListener(void);
	virtual void loadResources(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt);

	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);
	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	// Adjust mouse clipping area
	virtual void windowResized(Ogre::RenderWindow *rw);

	// Unattach OIS before window shutdown (very important under Linux)
	virtual void windowClosed(Ogre::RenderWindow *rw);

	Ogre::Root *mRoot;
	Ogre::Camera *mCamera;
	Ogre::SceneManager *mSceneMgr;
	Ogre::RenderWindow *mWindow;
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;

	Ogre::OverlaySystem *mOverlaySystem;

	// OgreBites
	OgreBites::InputContext mInputContext;
	OgreBites::SdkTrayManager *mTrayMgr;
	OgreBites::ParamsPanel *mDetailsPanel;   	// Sample details panel
	bool mCursorWasVisible;	// Was cursor visible before dialog appeared?
	bool mShutDown;

	//OIS Input devices
	OIS::InputManager *mInputManager;
	OIS::Mouse *mMouse;
	OIS::Keyboard *mKeyboard;

	// Added for Mac compatibility
	Ogre::String mResourcePath;

private:
	std::string mWindowName;

#ifdef OGRE_STATIC_LIB
	Ogre::StaticPluginLoader m_StaticPluginLoader;
#endif
};

//---------------------------------------------------------------------------

#endif // #ifndef __BaseApplication_h_

//---------------------------------------------------------------------------
