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
	m_parent_entity->m_position += m_parent_entity->m_velocity * dt;
}

