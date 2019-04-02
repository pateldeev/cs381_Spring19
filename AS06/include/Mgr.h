#ifndef MGR_H_
#define MGR_H_

class Engine;

class Mgr {
public:
	Mgr(Engine *engine);
	virtual ~Mgr();

	Engine *engine;

	virtual void Init(void) = 0;
	virtual void LoadLevel(void) = 0;
	virtual void Tick(float dt) = 0;
	virtual void Stop(void) = 0;

};

#endif /* MGR_H_ */
