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

	void SelectNextEntity();
	void SelectEntity(int index);
	bool AddEntityToGroup(unsigned int index);
	void AddNextUnselectedToGroup(void);
	void ClearEntityGroup(void);

	Entity381* GetMainSelected(void);
	Entity381* GetEntity(unsigned int index);
	bool IsEntitySelected(const Entity381* entity) const;

	void ChangeSelectedDesiredHeading(float change, bool accumulate = true);
	void ChangeSelectedDesiredSpeed(float change, bool accumulate = true);
	void ChangeSelectedDesiredAltitude(float change, bool accumulate = true);
	void StopSelectedEntities(void);


	void AddMoveCommandToSelectedEntities(const Ogre::Vector3 &target);
	void AddFollowCommandToSelectedEntities(const Entity381 *target);

	void Tick(float dt);

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
	void MakeBoundingBoxRed(void) {
		CreateNewMatertials();
		if (!mWireBoundingBox)
			mWireBoundingBox = new Ogre::WireBoundingBox();
		mWireBoundingBox->setMaterial("BaseRedLighting");
	}
	void MakeBoundingBoxBlue(void) {
		CreateNewMatertials();
		if (!mWireBoundingBox)
			mWireBoundingBox = new Ogre::WireBoundingBox();
		mWireBoundingBox->setMaterial("BaseBlueLighting");
	}
	void MakeBoundingBoxGreen(void) {
		CreateNewMatertials();
		if (!mWireBoundingBox)
			mWireBoundingBox = new Ogre::WireBoundingBox();
		mWireBoundingBox->setMaterial("BaseGreenLighting");
	}

	static void CreateNewMatertials(void) {
		static bool done = false;
		if (!done) {
			Ogre::MaterialPtr(Ogre::MaterialManager::getSingleton().getByName("BaseWhiteNoLighting"))->setLightingEnabled(true);
			Ogre::MaterialPtr mat_red = ((Ogre::MaterialPtr) Ogre::MaterialManager::getSingleton().getByName("BaseWhiteNoLighting"))->clone(
				"BaseRedLighting");
			mat_red->setAmbient(1.f, 0.f, 0.f);
			mat_red->setDiffuse(1.f, 0.f, 0.f, 0.f);

			Ogre::MaterialPtr mat_green = ((Ogre::MaterialPtr) Ogre::MaterialManager::getSingleton().getByName("BaseWhiteNoLighting"))->clone(
				"BaseGreenLighting");
			mat_green->setAmbient(0.f, 1.f, 0.f);
			mat_green->setDiffuse(0.f, 1.f, 0.f, 0.f);

			Ogre::MaterialPtr mat_blue = ((Ogre::MaterialPtr) Ogre::MaterialManager::getSingleton().getByName("BaseWhiteNoLighting"))->clone(
				"BaseBlueLighting");
			mat_blue->setAmbient(0.f, 0.f, 1.f);
			mat_blue->setDiffuse(0.f, 0.f, 1.f, 0.f);

			done = true;
		}
	}
};
#endif

#endif // #ifndef __EntityMgr_h_
