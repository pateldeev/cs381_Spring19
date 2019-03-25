#include <EntityMgr.h>
#include <Engine.h>
#include <Utils.h>

EntityMgr::EntityMgr(Engine *eng) :
	Mgr(eng) {
	selectedEntity = 0;
	count = 0;
	selectedEntityIndex = -1;
}

EntityMgr::~EntityMgr() {

}

void EntityMgr::CreateEntity(std::string meshfilename, Ogre::Vector3 pos) {
	Entity381 *ent = new Entity381(this->engine, meshfilename, pos, count);
	count++;
	entities.push_back(ent);
}

void EntityMgr::CreateDDG51(Ogre::Vector3 pos) {
	DDG51 *ent = new DDG51(this->engine, "ddg51.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}

void EntityMgr::CreateCarrier(Ogre::Vector3 pos) {
	Carrier *ent = new Carrier(this->engine, "cvn68.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}

void EntityMgr::CreateSpeedBoat(Ogre::Vector3 pos) {
	SpeedBoat *ent = new SpeedBoat(this->engine, "cigarette.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}

void EntityMgr::CreateFrigate(Ogre::Vector3 pos) {
	Frigate *ent = new Frigate(this->engine, "sleek.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}

void EntityMgr::CreateAlien(Ogre::Vector3 pos) {
	Alien *ent = new Alien(this->engine, "alienship.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}

void EntityMgr::CreateBanshee(Ogre::Vector3 pos) {
	Banshee *ent = new Banshee(this->engine, "banshee.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}

void EntityMgr::SelectNextEntity() {
	SelectEntity(selectedEntityIndex + 1);
}

void EntityMgr::SelectEntity(int index) {
	ClearEntityGroup();
	selectedEntityIndex = index % count;

	if (selectedEntity != 0)
		selectedEntity->sceneNode->showBoundingBox(false);

	selectedEntity = entities[selectedEntityIndex];
	selectedEntity->sceneNode->showBoundingBox(true);
#ifdef EDIT_BOUNDINGBOX_COLOR_EXPERIMENAL
	static_cast<BoudingBoxColorChangerExperimenatal*>(selectedEntity->sceneNode)->MakeBoundingBoxGreen();
#endif
}

bool EntityMgr::AddEntityToGroup(unsigned int index) {
	index %= count;
	if (int(index) != selectedEntityIndex) {
		if (selectedGroup.insert(index).second) {
			entities[index]->sceneNode->showBoundingBox(true);

#ifdef EDIT_BOUNDINGBOX_COLOR_EXPERIMENAL
			static_cast<BoudingBoxColorChangerExperimenatal*>(entities[index]->sceneNode)->MakeBoundingBoxBlue();
#endif
			return true;
		}
	}
	return false;
}

void EntityMgr::AddNextUnselectedToGroup(void) {
	if (selectedEntityIndex != -1) {
		int i = selectedEntityIndex + 1;
		while (i != selectedEntityIndex) {
			i = i % count;
			if (AddEntityToGroup(i++))
				break;
		}
	}
}

void EntityMgr::ClearEntityGroup(void) {
	for (unsigned int i : selectedGroup)
		entities[i]->sceneNode->showBoundingBox(false);
	selectedGroup.clear();
}

Entity381* EntityMgr::GetMainSelected(void) {
	return selectedEntity;
}

Entity381* EntityMgr::GetEntity(unsigned int index) {
	return entities[index];
}

bool EntityMgr::IsEntitySelected(const Entity381* entity) const {
	if (entity == selectedEntity)
		return true;

	for (unsigned int i : selectedGroup) {
		if (entities[i] == entity)
			return true;
	}

	return false;
}

void EntityMgr::ChangeSelectedDesiredHeading(float change, bool accumulate) {
	if (selectedEntity) {
		if (accumulate)
			selectedEntity->desiredHeading += change;
		else
			selectedEntity->desiredHeading = change;
	}
	for (unsigned int i : selectedGroup) {
		if (accumulate)
			entities[i]->desiredHeading += change;
		else
			entities[i]->desiredHeading = change;
	}
}

void EntityMgr::ChangeSelectedDesiredSpeed(float change, bool accumulate) {
	if (selectedEntity) {
		if (accumulate)
			selectedEntity->desiredSpeed += change;
		else
			selectedEntity->desiredSpeed = change;
	}
	for (unsigned int i : selectedGroup) {
		if (accumulate)
			entities[i]->desiredSpeed += change;
		else
			entities[i]->desiredSpeed = change;
	}
}

void EntityMgr::ChangeSelectedDesiredAltitude(float change, bool accumulate) {
	if (selectedEntity) {
		if (accumulate)
			selectedEntity->desiredAltitude += change;
		else
			selectedEntity->desiredAltitude = change;
	}
	for (unsigned int i : selectedGroup) {
		if (accumulate)
			entities[i]->desiredAltitude += change;
		else
			entities[i]->desiredAltitude = change;
	}
}

void EntityMgr::StopSelectedEntities(void) {
	selectedEntity->velocity = Ogre::Vector3::ZERO;
	selectedEntity->desiredSpeed = 0;
	selectedEntity->desiredHeading = selectedEntity->heading;
	selectedEntity->desiredAltitude = selectedEntity->altitude;
	selectedEntity->RemoveAllCommands();
	for (unsigned int i : selectedGroup) {
		entities[i]->velocity = Ogre::Vector3::ZERO;
		entities[i]->desiredSpeed = 0;
		entities[i]->desiredHeading = entities[i]->heading;
		entities[i]->desiredAltitude = entities[i]->altitude;
		entities[i]->RemoveAllCommands();
	}
}

void EntityMgr::AddMoveCommandToSelectedEntities(const Ogre::Vector3 &target) {
	selectedEntity->AddCommand(new CommandMoveTo(selectedEntity, target));
	for (unsigned int i : selectedGroup)
		entities[i]->AddCommand(new CommandMoveTo(entities[i], target));
}

void EntityMgr::AddFollowCommandToSelectedEntities(const Entity381 *target) {
#ifdef EDIT_BOUNDINGBOX_COLOR_EXPERIMENAL
	target->sceneNode->showBoundingBox(true);
	static_cast<BoudingBoxColorChangerExperimenatal*>(target->sceneNode)->MakeBoundingBoxRed();
#endif
	if (selectedEntity != target)
		selectedEntity->AddCommand(new CommandFollow(selectedEntity, target));
	for (unsigned int i : selectedGroup)
		if (entities[i] != target)
			entities[i]->AddCommand(new CommandFollow(entities[i], target));
}

void EntityMgr::CreateEntityOfTypeAtPosition(EntityTypes entType, Ogre::Vector3 pos) {
	switch (entType) {
	case DDG51Type:
		CreateDDG51(pos);
		break;
	case CarrierType:
		CreateCarrier(pos);
		break;
	case SpeedBoatType:
		CreateSpeedBoat(pos);
		break;
	case FrigateType:
		CreateFrigate(pos);
		break;
	case AlienType:
		CreateAlien(pos);
		break;
	case BansheeType:
		CreateBanshee(pos);
		break;
	default:
		CreateEntity("robot.mesh", pos);
		break;
	}
}

void EntityMgr::Tick(float dt) {
	for (int i = 0; i < count; i++)
		entities[i]->Tick(dt);
}
