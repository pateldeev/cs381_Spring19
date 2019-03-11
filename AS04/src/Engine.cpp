#include "Engine.h"

#include "EntityMgr.h"
#include "GameMgr.h"
#include "GfxMgr.h"
#include "InputMgr.h"

Engine::Engine(void) :
	m_entity_mgr(nullptr), m_game_mgr(nullptr), m_gfx_mgr(nullptr), m_input_mgr(nullptr), m_keep_running(true) {
}

Engine::~Engine(void) {

}

void Engine::Init(void) {
	m_entity_mgr = new EntityMgr(this);
	m_game_mgr = new GameMgr(this);
	m_gfx_mgr = new GfxMgr(this);
	m_input_mgr = new InputMgr(this);

	//--------------------------------------------------------------
	m_entity_mgr->Init();
	m_gfx_mgr->Init();
	m_input_mgr->Init(); // must initialize AFTER gfx manager
	m_game_mgr->Init();

	//--------------------------------------------------------------
	m_entity_mgr->LoadLevel();
	m_gfx_mgr->LoadLevel();
	m_input_mgr->LoadLevel();
	m_game_mgr->LoadLevel();
}

void Engine::Run(void) {
	const float MICROSECONDS_PER_SECOND = 1000000.0f;
	Ogre::Timer *timer = new Ogre::Timer();

	float oldTime = timer->getMicroseconds() / MICROSECONDS_PER_SECOND;
	float newTime = timer->getMicroseconds() / MICROSECONDS_PER_SECOND;
	float dt = newTime - oldTime;

	while (m_keep_running) {
		TickAll(dt);

		newTime = timer->getMicroseconds() / MICROSECONDS_PER_SECOND;
		dt = newTime - oldTime;
		oldTime = newTime;
	} // main must call cleanup or bad stuff happens->Cleanup()
}

void Engine::Cleanup(void) {
	m_input_mgr->Stop();
	m_gfx_mgr->Stop();
	m_entity_mgr->Stop();
	m_game_mgr->Stop();
}

void Engine::TickAll(float dt) {
	m_gfx_mgr->Tick(dt);
	m_input_mgr->Tick(dt);
	m_entity_mgr->Tick(dt);
	m_game_mgr->Tick(dt);
}

