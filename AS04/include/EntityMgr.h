#ifndef ENTITYMGR_H_
#define ENTITYMGR_H_

#include "Mgr.h"

#include "Entity381.h"

#include <vector>

class EntityMgr: public Mgr {

public:
	EntityMgr(Engine *engine);
	virtual ~EntityMgr(void);

public:
	virtual void Init(void) override final;
	virtual void LoadLevel(void) override final;
	virtual void Tick(float dt) override final;
	virtual void Stop(void) override final;

public:
	Entity381* CreateEntityOfTypeAtPosition(const EntityType type, const Ogre::Vector3 &position = Ogre::Vector3(0.f));

	bool SelectNextEntity(void); //returns false if no entities to select
	bool SelectPreviousEntity(void); //returns false if no entities to select
	bool SelectEntityByName(const std::string &name); //returns false if no entities with given name
	const Entity381* GetSelectedEntity(void) const; //returns nullptr if no entity selected

	bool AddEntityToGroup(const std::string &name); //returns false if no entities with given name
	void ClearGroup(void);

	bool ChangeSelectedDesiredSpeed(float amount); //returns false if no selected entity
	bool ChangeSelectedDesiredHeading(float amount); //returns false if no selected entity
	bool ChangeSelectedDesiredHeight(float amount); //returns false if no selected entity or object is not flying
	bool ResetSelectedSpeedAndHeading(void); //returns false if no selected entity

	bool ChangeGroupDesiredSpeed(float amount); //returns false if no entities in group
	bool ChangeGroupDesiredHeading(float amount); //returns false if no entities in group
	bool ResetGroupSpeedAndHeading(void); //returns false if no entities in group

	bool DisplaySelectedSpeedAndHeading(void) const; //returns false if no selected entity

private:
	void ChangeSelectedEntity(unsigned int position);

private:
	std::vector<Entity381*> m_entities;
	int m_selected_main; //-1 -> nothing selected
	std::vector<unsigned int> m_selected_group;

	Ogre::SceneManager *m_graphics_scene_manager;
};

#endif
