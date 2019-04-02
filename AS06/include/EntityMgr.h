#ifndef __EntityMgr_h_
#define __EntityMgr_h_

#include <Mgr.h>
#include <Entity381.h>
#include <Types381.h>

#include <vector>
#include <unordered_set>

class EntityMgr: public Mgr {
public:
	EntityMgr(Engine *engine);
	virtual ~EntityMgr();

	void CreateEntityOfTypeAtPosition(EntityTypes type, Ogre::Vector3 pos);

	void SelectNextEntity(bool make_sound = true);
	void SelectEntity(int index, bool make_sound = true);
	bool AddEntityToGroup(unsigned int index, bool make_sound = true);
	void AddNextUnselectedToGroup(bool make_sound = true);
	void ClearEntityGroup(void);

	Entity381* GetMainSelected(void);
	Entity381* GetEntity(unsigned int index);
	bool IsEntitySelected(const Entity381* entity) const;

	void ChangeSelectedDesiredHeading(float change, bool accumulate = true);
	void ChangeSelectedDesiredSpeed(float change, bool accumulate = true);
	void ChangeSelectedDesiredAltitude(float change, bool accumulate = true);
	void StopSelectedEntities(void);

	void AddMoveToCommandToSelectedEntities(const Ogre::Vector3 &target, bool remove_past_commands = false);
	void AddInterceptCommandToSelectedEntities(const Entity381 *target, bool remove_past_commands = false);
	void AddFollowCommandToSelectedEntities(const Entity381 *target, bool remove_past_commands = false);

	virtual void Init(void) override;
	virtual void LoadLevel(void) override;
	virtual void Tick(float dt) override;
	virtual void Stop(void) override;

	int count;

private:
	void CreateEntity(std::string meshfilename, Ogre::Vector3 pos);
	void CreateDDG51(Ogre::Vector3 pos);
	void CreateCarrier(Ogre::Vector3 pos);
	void CreateSpeedBoat(Ogre::Vector3 pos);
	void CreateFrigate(Ogre::Vector3 pos);
	void CreateAlien(Ogre::Vector3 pos);
	void CreateBanshee(Ogre::Vector3 pos);

private:
	std::vector<Entity381*> entities;
	Entity381* selectedEntity;
	int selectedEntityIndex;
	std::unordered_set<unsigned int> selectedGroup; //hold entities selected in group - not main one
};

#define EDIT_BOUNDINGBOX_COLOR_EXPERIMENAL //experimental function that does unsafe static casting to access protected member of Ogre::SceneNode to change bounding box color

#ifdef EDIT_BOUNDINGBOX_COLOR_EXPERIMENAL
#include <OGRE/OgreWireBoundingBox.h>
class BoudingBoxColorChangerExperimenatal: public Ogre::SceneNode {
public:
	void MakeBoundingBoxGreen(void) {
		CreateNewMatertials();
		if (!mWireBoundingBox)
			mWireBoundingBox = new Ogre::WireBoundingBox();
		mWireBoundingBox->setMaterial("BaseGreenLighting");
	}
	void MakeBoundingBoxBlue(void) {
		CreateNewMatertials();
		if (!mWireBoundingBox)
			mWireBoundingBox = new Ogre::WireBoundingBox();
		mWireBoundingBox->setMaterial("BaseBlueLighting");
	}
	void MakeBoundingBoxRed(void) {
		CreateNewMatertials();
		if (!mWireBoundingBox)
			mWireBoundingBox = new Ogre::WireBoundingBox();
		mWireBoundingBox->setMaterial("BaseRedLighting");
	}
	void MakeBoundingBoxOrange(void) {
		CreateNewMatertials();
		if (!mWireBoundingBox)
			mWireBoundingBox = new Ogre::WireBoundingBox();
		mWireBoundingBox->setMaterial("BaseOrangeLighting");
	}
	void MakeBoundingBoxBlack(void) {
		CreateNewMatertials();
		if (!mWireBoundingBox)
			mWireBoundingBox = new Ogre::WireBoundingBox();
		mWireBoundingBox->setMaterial("BaseBlackLighting");
	}

	static void CreateNewMatertials(void) {
		static bool done = false;
		if (!done) {
			Ogre::MaterialPtr(Ogre::MaterialManager::getSingleton().getByName("BaseWhiteNoLighting"))->setLightingEnabled(true);

			//green
			Ogre::MaterialPtr mat_green = ((Ogre::MaterialPtr) Ogre::MaterialManager::getSingleton().getByName("BaseWhiteNoLighting"))->clone(
				"BaseGreenLighting");
			mat_green->setAmbient(0.f, 1.f, 0.f);
			mat_green->setDiffuse(0.f, 1.f, 0.f, 0.f);

			//blue
			Ogre::MaterialPtr mat_blue = ((Ogre::MaterialPtr) Ogre::MaterialManager::getSingleton().getByName("BaseWhiteNoLighting"))->clone(
				"BaseBlueLighting");
			mat_blue->setAmbient(0.f, 0.f, 1.f);
			mat_blue->setDiffuse(0.f, 0.f, 1.f, 0.f);

			//red
			Ogre::MaterialPtr mat_red = ((Ogre::MaterialPtr) Ogre::MaterialManager::getSingleton().getByName("BaseWhiteNoLighting"))->clone(
				"BaseRedLighting");
			mat_red->setAmbient(1.f, 0.f, 0.f);
			mat_red->setDiffuse(1.f, 0.f, 0.f, 0.f);

			//orange
			Ogre::MaterialPtr mat_orange = ((Ogre::MaterialPtr) Ogre::MaterialManager::getSingleton().getByName("BaseWhiteNoLighting"))->clone(
				"BaseOrangeLighting");
			mat_orange->setAmbient(1.f, 0.65, 0.f);
			mat_orange->setDiffuse(1.f, 0.65, 0.f, 0.f);

			//black
			Ogre::MaterialPtr mat_black = ((Ogre::MaterialPtr) Ogre::MaterialManager::getSingleton().getByName("BaseWhiteNoLighting"))->clone(
				"BaseBlackLighting");
			mat_black->setAmbient(0.f, 0.f, 0.f);
			mat_black->setDiffuse(0.f, 0.f, 0.f, 0.f);

			done = true;
		}
	}
};
#endif

#endif // #ifndef __EntityMgr_h_
