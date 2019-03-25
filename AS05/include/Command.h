#ifndef __Command_h_
#define __Command_h_

class Entity381;

class Command {
public:
	virtual ~Command(void);

	virtual void Tick(float dt) = 0;
	virtual void Init(void);
	virtual void Stop(void);

	bool IsRunning(void) const;

protected:
	Command(Entity381 *parent); //only meant to be created by sub classes

protected:
	Entity381 *m_parent;
	bool m_running;
};

#include <OGRE/OgreVector3.h>

class CommandMoveTo: public Command {
public:
	CommandMoveTo(Entity381 *parent, const Ogre::Vector3 &position);
	virtual ~CommandMoveTo(void);

	virtual void Tick(float dt) override;
	virtual void Init(void) override;
	virtual void Stop(void) override;

protected:
	Ogre::Vector3 m_target;
	float m_distance_to_target;

private:
	static float acceptable_error;
};

class CommandFollow: public CommandMoveTo {
public:
	CommandFollow(Entity381 *parent, const Entity381 *target);
	virtual ~CommandFollow(void);

	virtual void Tick(float dt) override;

private:
	const Entity381* m_following;
};

#endif // #ifndef __Command_h_
