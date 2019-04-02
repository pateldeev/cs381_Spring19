#ifndef GAMEMGR_H_
#define GAMEMGR_H_

#include <Mgr.h>

#include <OGRE/OgreSceneNode.h>

class GameMgr: public Mgr {
public:
	GameMgr(Engine *engine);
	virtual ~GameMgr();

	virtual void Init(void) override;
	virtual void LoadLevel(void) override;
	virtual void Tick(float dt) override;
	virtual void Stop(void) override;

	void MakeGround();
	void MakeSky();
	void MakeEntities();

	Ogre::SceneNode *cameraNode;
};

#endif /* GAMEMGR_H_ */
