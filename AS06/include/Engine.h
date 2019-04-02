#ifndef ENGINE_H_
#define ENGINE_H_

class EntityMgr;
class GameMgr;
class GfxMgr;
class InputMgr;
class SoundMgr;

class Engine {
public:
	Engine();
	virtual ~Engine();

	EntityMgr *entityMgr;
	GameMgr *gameMgr;
	GfxMgr *gfxMgr;
	InputMgr *inputMgr;
	SoundMgr *soundMgr;

	void Init(void);
	void Run(void);
	void TickAll(float dt);
	void Cleanup(void);

	bool keepRunning;
};

#endif /* ENGINE_H_ */
