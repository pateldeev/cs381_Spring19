#include <GfxMgr.h>
#include <Entity381.h>

std::string IntToString(int x) {
	char tmp[10000];
	sprintf(tmp, "%i", x);
	return std::string(tmp);
}

Entity381::Entity381(Engine *engine, std::string meshfname, Ogre::Vector3 pos, int ident) {

	this->engine = engine;

	meshfilename = meshfname;
	position = pos;
	velocity = Ogre::Vector3(0, 0, 0);
	identity = ident;

	name = meshfname + IntToString(identity);

	ogreEntity = engine->gfxMgr->mSceneMgr->createEntity(meshfilename);
	sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(pos);
	sceneNode->attachObject(ogreEntity);

	Physics2D* phx = new Physics2D(this);
	aspects.push_back((Aspect*) phx);
	Renderable * renderable = new Renderable(this);
	aspects.push_back((Aspect*) renderable);

	this->acceleration = 0;
	this->desiredHeading = this->heading = 0;
	this->turnRate = 0;
	this->desiredSpeed = this->speed = 0;
	this->minSpeed = this->maxSpeed = 0;
	this->desiredAltitude = this->altitude = position.y;
	this->climbRate = 0;

}

Entity381::~Entity381() {

}

void Entity381::Tick(float dt) {
	if (!commands.empty()) {
		commands.front()->Tick(dt);
		if (!commands.front()->IsRunning()) {
			delete commands.front();
			commands.pop();

			if (!commands.empty())
				commands.front()->Init();
		}
	}

	for (unsigned int i = 0; i < aspects.size(); i++)
		aspects[i]->Tick(dt);
}

void Entity381::AddCommand(Command *command) {
	command->Init();
	commands.push(command);
}

void Entity381::RemoveAllCommands(void) {
	while (!commands.empty()) {
		commands.front()->Stop();
		delete commands.front();
		commands.pop();
	}
}

//-------------------------------------------------------------------------------------------------------------------------------
DDG51::DDG51(Engine *engine, std::string meshfname, Ogre::Vector3 pos, int ident) :
	Entity381(engine, meshfname, pos, ident) {
	this->minSpeed = 0;
	this->maxSpeed = 32.0f; //meters per second...
	this->acceleration = 10.0f; // fast
	this->turnRate = 20.0f; //4 degrees per second
}

DDG51::~DDG51() {

}

//-------------------------------------------------------------------------------------------------------------------------------
Carrier::Carrier(Engine *engine, std::string meshfname, Ogre::Vector3 pos, int ident) :
	Entity381(engine, meshfname, pos, ident) {
	this->minSpeed = 0;
	this->maxSpeed = 40.0f; //meters per second...
	this->acceleration = 2.0f; // slow
	this->turnRate = 10.0f; //2 degrees per second
}

Carrier::~Carrier() {

}
//-------------------------------------------------------------------------------------------------------------------------------

SpeedBoat::SpeedBoat(Engine *engine, std::string meshfname, Ogre::Vector3 pos, int ident) :
	Entity381(engine, meshfname, pos, ident) {
	this->minSpeed = 0;
	this->maxSpeed = 60.0f; //meters per second...
	this->acceleration = 10.0f; // slow
	this->turnRate = 30.0f; //2 degrees per second
}

SpeedBoat::~SpeedBoat() {

}
//-------------------------------------------------------------------------------------------------------------------------------

Frigate::Frigate(Engine *engine, std::string meshfname, Ogre::Vector3 pos, int ident) :
	Entity381(engine, meshfname, pos, ident) {
	this->minSpeed = 0;
	this->maxSpeed = 30.0f; //meters per second...
	this->acceleration = 10.0f; // slow
	this->turnRate = 20.0f; //2 degrees per second
}

Frigate::~Frigate() {

}

//-------------------------------------------------------------------------------------------------------------------------------
Alien::Alien(Engine *engine, std::string meshfname, Ogre::Vector3 pos, int ident) :
	Entity381(engine, meshfname, pos, ident) {
	this->minSpeed = 0;
	this->maxSpeed = 100.0f; //meters per second...
	this->acceleration = 20.0f; // slow
	this->turnRate = 40.0f; //2 degrees per second
}

Alien::~Alien() {

}
//-------------------------------------------------------------------------------------------------------------------------------
Banshee::Banshee(Engine *engine, std::string meshfname, Ogre::Vector3 pos, int ident) :
	Entity381(engine, meshfname, pos, ident) {
	this->minSpeed = 0;
	this->maxSpeed = 250.0f; //meters per second...
	this->acceleration = 30.0f; // slow
	this->turnRate = 45.0f; //2 degrees per second

	this->climbRate = 10.f; //banshee can fly

	//banshee can move up/down
	Physics3D* phx3D = new Physics3D((Entity381*) this);
	aspects.push_back((Aspect*) phx3D);
}

Banshee::~Banshee() {
}
//-------------------------------------------------------------------------------------------------------------------------------

