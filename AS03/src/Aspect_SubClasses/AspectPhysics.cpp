/*
 -----------------------------------------------------------------------------
 Filename: AspectPhysics.cpp
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains implementation of AspectPhysics class
 */

#include "Aspect_SubClasses/AspectPhysics.h"
#include "Entity381.h"

AspectPhysics::AspectPhysics(Entity381 *parent) :
	Aspect(parent) {
}

AspectPhysics::~AspectPhysics(void) {

}

void AspectPhysics::Tick(float dt) {
	m_parent_entity->m_heading = getNewHeading(m_parent_entity->m_heading, m_parent_entity->m_heading_desired, m_parent_entity->m_turning_rate * dt);
	m_parent_entity->m_speed = getNewSpeed(m_parent_entity->m_speed, m_parent_entity->m_speed_desired, m_parent_entity->m_acceleration * dt);

	m_parent_entity->m_velocity = getVelocityInDirectionOfHeading(m_parent_entity->m_heading, m_parent_entity->m_speed);

	m_parent_entity->m_position += m_parent_entity->m_velocity * dt;
}

float AspectPhysics::getNewHeading(float current, float desired, float max_change, float acceptable_error) {
	float diff = desired - current;
	if (desired < current)
		diff += 360;

	float new_heading;
	if (diff <= 180)
		new_heading = (diff > max_change) ? current + max_change : desired; //turn counterclockwise
	else
		new_heading = (360 - diff > max_change) ? current - max_change : desired; //turn clockwise

	new_heading = std::fmod(new_heading, 360);
	if (new_heading < 0)
		new_heading += 360;
	else if (new_heading >= 360)
		new_heading -= 360;

	return new_heading;
}

float AspectPhysics::getNewSpeed(float current, float desired, float max_change, float acceptable_error) {
	float diff = desired - current;

	if (diff < -max_change)
		return current - max_change;
	else if (diff < -acceptable_error)
		return desired;
	else if (diff < acceptable_error)
		return current;
	else if (diff < max_change)
		return desired;
	else if (diff > max_change)
		return current + max_change;
	else
		return -1; //error - should not happen
}

Ogre::Vector3 AspectPhysics::getVelocityInDirectionOfHeading(float heading, float speed) {
	Ogre::Vector3 velocity(0.f);
	velocity.y = 0.f; //no up down motion

//set z component to correct orientation worry about scaling by speed later
	if (heading > 89 && heading < 91)
		velocity.z = -1.f;
	else if (heading > 269 && heading < 270)
		velocity.z = 1.f;
	else
		velocity.z = -std::sin(heading * M_PI / 180); //set z component - assume speed = 1;

//set x component to correct orientation worry about scaling by speed later
	if (heading < 1 || heading > 369)
		velocity.x = 1.f;
	else if (heading > 179 && heading < 181)
		velocity.x = -1.f;
	else
		velocity.x = std::cos(heading * M_PI / 180); //set x component - assume speed = 1;

	return (speed * velocity);
}
