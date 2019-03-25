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
	if (entity->altitude < entity->desiredAltitude - acceptableAltitudeErr) //need to move up
		entity->altitude += entity->climbRate * dt;
	else if (entity->altitude > entity->desiredAltitude + acceptableAltitudeErr) //need to move down
		entity->altitude -= entity->climbRate * dt;

	entity->position.y = entity->altitude;
}
