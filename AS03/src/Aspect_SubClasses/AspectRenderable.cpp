/*
 -----------------------------------------------------------------------------
 Filename: AspectRenderable.cpp
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 Contains implementation of AspectRenderable class
 */

#include "Aspect_SubClasses/AspectRenderable.h"
#include "Entity381.h"

AspectRenderable::AspectRenderable(Entity381 *parent) :
	Aspect(parent) {
}

AspectRenderable::~AspectRenderable(void) {

}

void AspectRenderable::Tick(float dt) {
	m_parent_entity->m_scene_node->setPosition(m_parent_entity->m_position);

	float yaw = m_parent_entity->m_scene_node->getOrientation().getYaw().valueDegrees(); //get current yaw (-180,180)
	if (yaw < 0)
		yaw += 360; //get into range [0, 360)
	yaw = m_parent_entity->m_heading - yaw; //amount we need to change by

	m_parent_entity->m_scene_node->yaw(Ogre::Degree(yaw), Ogre::Node::TransformSpace::TS_WORLD);
}

