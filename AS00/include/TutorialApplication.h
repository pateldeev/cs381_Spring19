/*
 -----------------------------------------------------------------------------
 Filename:    TutorialApplication.h
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

#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "BaseApplication.h"

//---------------------------------------------------------------------------

class TutorialApplication: public BaseApplication {
public:
	TutorialApplication(const std::string &windowName = "TutorialApplication Render Window");
	virtual ~TutorialApplication(void);

protected:
	virtual void createScene(void);
};

//---------------------------------------------------------------------------

#endif // #ifndef __TutorialApplication_h_

//---------------------------------------------------------------------------
