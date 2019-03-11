#ifndef ENGINE_H_
#define ENGINE_H_

class EntityMgr;
class GameMgr;
class GfxMgr;
class InputMgr;

class Engine {

public:
	Engine(void);
	virtual ~Engine(void);

	EntityMgr *m_entity_mgr;
	GameMgr *m_game_mgr;
	GfxMgr *m_gfx_mgr;
	InputMgr *m_input_mgr;

	void Init(void);
	void Run(void);
	void TickAll(float dt);
	void Cleanup(void);

	bool m_keep_running;
};

#endif
