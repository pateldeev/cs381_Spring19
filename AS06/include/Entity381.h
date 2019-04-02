#ifndef __Entity381_h_
#define __Entity381_h_

#include <OGRE/OgreEntity.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreVector3.h>

#include <Aspect.h>
#include <Engine.h>

class Entity381 {
public:
	Entity381(Engine *engine, std::string meshfilename, Ogre::Vector3 pos, int identity);
	virtual ~Entity381();

	void RemoveAllCommands(void);
	void AddCommand(Command *c, bool remove_past = false);

	Engine *engine;

	//static data
	int identity;
	std::string name;
	std::string meshfilename;
	Ogre::SceneNode* sceneNode;
	Ogre::Entity* ogreEntity;
	float acceleration, turnRate;
	float minSpeed, maxSpeed;

	std::string m_selection_sound;
	unsigned int m_audio_id;

	//dynamic data
	Ogre::Vector3 position;
	Ogre::Vector3 velocity;

	float desiredHeading, desiredSpeed;
	float heading, speed;
	float altitude;
	float desiredAltitude;
	float roll;
	float desiredRoll;
	float climbRate;

	UnitAI *ai;

	void Tick(float dt);

	void MakeSelectionSound(void);

protected:
	std::vector<Aspect*> aspects;
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
