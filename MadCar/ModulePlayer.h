#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 2000.0f
#define TURN_DEGREES 25.0f * DEGTORAD
#define BRAKE_POWER 1000.0f
#define PLAYING_TIME 150.0f
#define FRONTFLIP_TIME 1.5f
#define BACKFLIP_TIME 2.4f
#define SIDEFLIP_TIME 1.75f
#define TURNSIDE_TIME 1.7F
#define COINS 10


enum Gamestate
{
	READY,
	PLAYING,
	END
};

enum state
{
	GROUND,
	AIR,
	FRONTFLIP,
	BACKFLIP,
	LEFTFLIP,
	RIGHTFLIP,
	TURNRIGHT,
	TURNLEFT
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

	void GameProgress();
	void Reset();
	void Move();
	void Flips();
	void Score();
	bool CheckVehicleCollision(float x, float y, float z);

public:
	
	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;

	state vehiclestate;

	float* originalpos;
	mat4x4 vehicle_transf;
	vec3 X;
	vec3 Y;
	vec3 Z;


	Gamestate play;
	Timer time;
	float gameplaytimer;
	int score;
	Timer fliptimer;
	float endflip;
	int turbo;
	int flip;
	int jump;
	int coins;
	int finale;
	int WinSound;
	bool win;
};