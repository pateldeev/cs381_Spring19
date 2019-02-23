/*
 -----------------------------------------------------------------------------
 Filename: AspectRotator.cpp
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains implementation of AspectRotator class
 */

#include "Aspect_SubClasses/AspectRotator.h"
#include "Entity381.h"

AspectRotator::AspectRotator(Entity381 *parent, float rotation_speed) :
	Aspect(parent), m_rotation_speed(rotation_speed) {
}

AspectRotator::~AspectRotator(void) {

}

void AspectRotator::Tick(float dt) {
	m_parent_entity->m_scene_node->yaw(Ogre::Radian(dt * m_rotation_speed), Ogre::Node::TransformSpace::TS_LOCAL);
}

