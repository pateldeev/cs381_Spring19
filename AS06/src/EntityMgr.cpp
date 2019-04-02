#include <EntityMgr.h>
#include <SoundMgr.h>
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

void EntityMgr::SelectNextEntity(bool make_sound) {
	SelectEntity(selectedEntityIndex + 1, make_sound);
}

void EntityMgr::SelectEntity(int index, bool make_sound) {
	ClearEntityGroup();
	selectedEntityIndex = index % count;
	selectedEntity = entities[selectedEntityIndex];
	if (make_sound)
		selectedEntity->MakeSelectionSound();
}

bool EntityMgr::AddEntityToGroup(unsigned int index, bool make_sound) {
	index %= count;
	if (int(index) != selectedEntityIndex) {
		if (selectedGroup.insert(index).second && make_sound) {
			entities[index]->MakeSelectionSound();
		}
	}
	return false;
}

void EntityMgr::AddNextUnselectedToGroup(bool make_sound) {
	if (selectedEntityIndex != -1) {
		int i = selectedEntityIndex + 1;
		while (i != selectedEntityIndex) {
			i = i % count;
			if (AddEntityToGroup(i++, make_sound))
				break;
		}
	}
}

void EntityMgr::ClearEntityGroup(void) {
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

void EntityMgr::AddMoveToCommandToSelectedEntities(const Ogre::Vector3 &target, bool remove_past_commands) {
	selectedEntity->AddCommand(new CommandMoveTo(selectedEntity, target), remove_past_commands);
	for (unsigned int i : selectedGroup)
		entities[i]->AddCommand(new CommandMoveTo(entities[i], target), remove_past_commands);
}

void EntityMgr::AddInterceptCommandToSelectedEntities(const Entity381 *target, bool remove_past_commands) {
	if (selectedEntity != target)
		selectedEntity->AddCommand(new CommandIntercept(selectedEntity, target), remove_past_commands);
	for (unsigned int i : selectedGroup)
		if (entities[i] != target)
			entities[i]->AddCommand(new CommandIntercept(entities[i], target), remove_past_commands);
}

void EntityMgr::AddFollowCommandToSelectedEntities(const Entity381 *target, bool remove_past_commands) {
	if (selectedEntity != target)
		selectedEntity->AddCommand(new CommandFollow(selectedEntity, target), remove_past_commands);
	for (unsigned int i : selectedGroup)
		if (entities[i] != target)
			entities[i]->AddCommand(new CommandFollow(entities[i], target), remove_past_commands);
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

void EntityMgr::Init(void) {

}
void EntityMgr::LoadLevel(void) {
	for (Entity381* e : entities)
		engine->soundMgr->loadAudio(e->m_selection_sound, &e->m_audio_id, false);
}

void EntityMgr::Tick(float dt) {
	for (int i = 0; i < count; i++)
		entities[i]->Tick(dt);
	if (selectedEntity)
		selectedEntity->ai->DrawBoundingBox(true);

	selectedEntity->sceneNode->showBoundingBox(true);
#ifdef EDIT_BOUNDINGBOX_COLOR_EXPERIMENAL
	static_cast<BoudingBoxColorChangerExperimenatal*>(selectedEntity->sceneNode)->MakeBoundingBoxGreen();
#endif

	for (unsigned int i : selectedGroup) {
		entities[i]->sceneNode->showBoundingBox(true);
#ifdef EDIT_BOUNDINGBOX_COLOR_EXPERIMENAL
		static_cast<BoudingBoxColorChangerExperimenatal*>(entities[i]->sceneNode)->MakeBoundingBoxBlue();
#endif

	}
}

void EntityMgr::Stop(void) {

}
