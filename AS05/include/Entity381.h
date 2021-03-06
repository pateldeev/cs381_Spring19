#ifndef __Entity381_h_
#define __Entity381_h_

#include <OGRE/OgreEntity.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreVector3.h>

#include <Aspect.h>
#include <Engine.h>
#include <Command.h>

class Entity381 {
public:
	Entity381(Engine *engine, std::string meshfilename, Ogre::Vector3 pos, int identity);
	virtual ~Entity381();

	Engine *engine;

	//static data
	int identity;
	std::string name;
	std::string meshfilename;
	Ogre::SceneNode* sceneNode;
	Ogre::Entity* ogreEntity;
	float acceleration, turnRate;
	float minSpeed, maxSpeed;

	//dynamic data
	Ogre::Vector3 position;
	Ogre::Vector3 velocity;

	float desiredHeading, desiredSpeed;
	float heading, speed;
	float altitude;
	float desiredAltitude;
	float climbRate;

	void Tick(float dt);

	void AddCommand(Command *command);
	void RemoveAllCommands(void);

protected:
	std::vector<Aspect*> aspects;
	std::queue<Command*> commands;
};

class Carrier: Entity381 {
public:
	Carrier(Engine *engine, std::string meshfilename, Ogre::Vector3 pos, int identity);
	virtual ~Carrier();

};

class DDG51: Entity381 {
public:
	DDG51(Engine *engine, std::string meshfilename, Ogre::Vector3 pos, int identity);
	virtual ~DDG51();

};

class SpeedBoat: Entity381 {
public:
	SpeedBoat(Engine *engine, std::string meshfilename, Ogre::Vector3 pos, int identity);
	virtual ~SpeedBoat();

};

class Frigate: Entity381 {
public:
	Frigate(Engine *engine, std::string meshfilename, Ogre::Vector3 pos, int identity);
	virtual ~Frigate();

};

class Alien: Entity381 {
public:
	Alien(Engine *engine, std::string meshfilename, Ogre::Vector3 pos, int identity);
	virtual ~Alien();

};

class Banshee: Entity381 {
public:
	Banshee(Engine *engine, std::string meshfilename, Ogre::Vector3 pos, int identity);
	virtual ~Banshee();

};

#endif // #ifndef __Entity381_h_
