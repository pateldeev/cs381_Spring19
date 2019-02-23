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
}

