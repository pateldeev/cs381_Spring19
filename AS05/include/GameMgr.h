#ifndef GAMEMGR_H_
#define GAMEMGR_H_

#include <Mgr.h>

#include <OGRE/OgreSceneNode.h>

class GameMgr: public Mgr {
public:
	GameMgr(Engine *engine);
	virtual ~GameMgr();

	void Init();
	void LoadLevel();
	void Tick(float dt);

	void MakeGround();
	void MakeSky();
	void MakeEntities();

	Ogre::SceneNode *cameraNode;
};

#endif /* GAMEMGR_H_ */
