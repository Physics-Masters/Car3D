#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 2000.0f
#define TURN_DEGREES 25.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

enum state
{
	GROUND,
	AIR,
	FLIP
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	btVector3 GetVehiclePosition();

public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;

	state vehiclestate;

	mat4x4 vehicle_transf;
	vec3 X;
	vec3 Y;
	vec3 Z;
};