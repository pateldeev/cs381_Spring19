#include <Command.h>
#include <Entity381.h>
#include <EntityMgr.h>

Command::~Command(void) {

}

void Command::Init(void) {
	m_running = true;
}

void Command::Stop(void) {
	m_running = false;
}

bool Command::Done(void) const {
	return !m_running;
}

void Command::DrawBoundingBox(bool draw_all) const {
	m_parent->sceneNode->showBoundingBox(true);
#ifdef EDIT_BOUNDINGBOX_COLOR_EXPERIMENAL
	static_cast<BoudingBoxColorChangerExperimenatal*>(m_parent->sceneNode)->MakeBoundingBoxBlack();
#endif
}

Command::Command(Entity381 *parent) :
	m_parent(parent), m_running(false) {

}

float CommandMoveTo::acceptable_error = 12.f;

CommandMoveTo::CommandMoveTo(Entity381 *parent, const Ogre::Vector3 &position) :
	Command(parent), m_target(position), m_distance_to_target(0.f) {
}

CommandMoveTo::~CommandMoveTo(void) {

}

void CommandMoveTo::Tick(float dt) {
	m_distance_to_target = m_parent->position.distance(m_target);
	float speed_max = m_distance_to_target / 2;

	if (m_distance_to_target < acceptable_error) {
		m_parent->desiredSpeed = 0;
		m_running = false;
	} else {
		float heading_to_target = Ogre::Vector3::UNIT_X.angleBetween(m_target - m_parent->position).valueDegrees();
		if (m_target.z < m_parent->position.z)
			heading_to_target = 360 - heading_to_target;
		m_parent->desiredHeading = heading_to_target;
		m_parent->desiredSpeed = std::min(m_parent->maxSpeed, speed_max);
	}
}

void CommandMoveTo::Init(void) {
	m_parent->desiredSpeed = m_parent->maxSpeed;
	m_distance_to_target = m_parent->position.distance(m_target);
	Command::Init();
}

float CommandFollow::max_follow_distance = 50.f;

CommandFollow::CommandFollow(Entity381 *parent, const Entity381 *target) :
	CommandMoveTo(parent, target->position), m_following(target) {
}

CommandFollow::~CommandFollow(void) {

}

void CommandFollow::Tick(float dt) {
	m_parent->desiredSpeed = m_parent->maxSpeed;
	CommandMoveTo::Tick(dt);

	if (m_parent->position.distance(m_target) < CommandFollow::max_follow_distance)
		m_parent->desiredSpeed = m_following->speed;

	if (m_parent->speed > 1)
		m_target = m_following->position + (m_following->velocity * dt * (m_distance_to_target / m_parent->speed));
	else
		m_target = m_following->position;

	m_target = m_following->position;

	m_running = true; //prevent command from ending once target reached
}

void CommandFollow::DrawBoundingBox(bool draw_all) const {
	Command::DrawBoundingBox();
	if (draw_all) {
		m_following->sceneNode->showBoundingBox(true);
#ifdef EDIT_BOUNDINGBOX_COLOR_EXPERIMENAL
		static_cast<BoudingBoxColorChangerExperimenatal*>(m_following->sceneNode)->MakeBoundingBoxOrange();
#endif
	}
}

CommandIntercept::CommandIntercept(Entity381 *parent, const Entity381 *target) :
	CommandMoveTo(parent, target->position), m_intercept_target(target) {
}

CommandIntercept::~CommandIntercept(void) {

}

void CommandIntercept::Tick(float dt) {
	CommandMoveTo::Tick(dt);

	if (m_parent->speed > 1)
		m_target = m_intercept_target->position + (m_intercept_target->velocity * dt * (m_distance_to_target / m_parent->speed));
	else
		m_target = m_intercept_target->position;

	m_parent->desiredSpeed = m_parent->maxSpeed;
	m_running = true; //prevent command from ending once target reached
}

void CommandIntercept::DrawBoundingBox(bool draw_all) const {
	Command::DrawBoundingBox();
	if (draw_all) {
		m_intercept_target->sceneNode->showBoundingBox(true);
#ifdef EDIT_BOUNDINGBOX_COLOR_EXPERIMENAL
		static_cast<BoudingBoxColorChangerExperimenatal*>(m_intercept_target->sceneNode)->MakeBoundingBoxRed();
#endif
	}
}
