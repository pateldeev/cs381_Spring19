#include <Aspect.h>
#include <Entity381.h>
#include <Utils.h>

Physics3D::Physics3D(Entity381* ent) :
	Aspect(ent) {

}

Physics3D::~Physics3D() {

}

void Physics3D::Tick(float dt) {
	const float acceptableAltitudeErr = 0.25;
	if (entity->altitude < entity->desiredAltitude - acceptableAltitudeErr) { //need to move up
		float altitude_increase = entity->climbRate * dt;
		entity->desiredRoll = -30;
		entity->altitude += altitude_increase;
	} else if (entity->altitude > entity->desiredAltitude + acceptableAltitudeErr) { //need to move down
		float altitude_decrease = entity->climbRate * dt;
		entity->desiredRoll = 30;
		entity->altitude -= altitude_decrease;
	} else {
		entity->desiredRoll = 0;
	}
	entity->position.y = entity->altitude;
}
