#include <GfxMgr.h>
#include <SoundMgr.h>
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
	ai = new UnitAI(this);
	aspects.push_back((Aspect*) ai);

	this->acceleration = 0;
	this->desiredHeading = this->heading = 0;
	this->turnRate = 0;
	this->desiredSpeed = this->speed = 0;
	this->minSpeed = this->maxSpeed = 0;
	this->desiredAltitude = this->altitude = position.y;
	this->roll = 0;
	this->desiredRoll = 0;
	this->climbRate = 0;

	m_audio_id = 0;
}

Entity381::~Entity381() {
	for (Aspect *a : aspects)
		delete a;
}

void Entity381::RemoveAllCommands(void) {
	ai->RemoveAllCommands();
}

void Entity381::AddCommand(Command *c, bool remove_past) {
	if (remove_past)
		ai->SetCommand(c);
	else
		ai->AddCommand(c);
}

void Entity381::Tick(float dt) {
	sceneNode->showBoundingBox(false);
	for (Aspect *a : aspects)
		a->Tick(dt);
	ai->DrawBoundingBox();
}

void Entity381::MakeSelectionSound(void) {
	engine->soundMgr->stopAllAudio();
	engine->soundMgr->playAudio(m_audio_id, true);
}

//-------------------------------------------------------------------------------------------------------------------------------
DDG51::DDG51(Engine *engine, std::string meshfname, Ogre::Vector3 pos, int ident) :
	Entity381(engine, meshfname, pos, ident) {
	this->minSpeed = 0;
	this->maxSpeed = 32.0f; //meters per second...
	this->acceleration = 10.0f; // fast
	this->turnRate = 20.0f; //4 degrees per second
	m_selection_sound = "assets/sounds/Selection_Destroyer.ogg";
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
	m_selection_sound = "assets/sounds/Selection_Carrier.ogg";
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
	m_selection_sound = "assets/sounds/Selection_Speedboat.ogg";
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
	m_selection_sound = "assets/sounds/Selection_Frigate.ogg";
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
	m_selection_sound = "assets/sounds/Selection_Alien.ogg";
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
	m_selection_sound = "assets/sounds/Selection_Banshee.ogg";
}

Banshee::~Banshee() {
}
//-------------------------------------------------------------------------------------------------------------------------------

