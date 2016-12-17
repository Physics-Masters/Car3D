#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:
	/*
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];
	*/

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;
	Cube wall1;
	Cube light1;
	Cube light2;
	PhysBody3D* wall1body;
	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;
	Cube c1;
	PhysBody3D* c1body;
	Cube b1;
	PhysBody3D* b1body;
	Cube b2;
	PhysBody3D* b2body;
	Cube Table1;
	PhysBody3D* Table1body;
	Cube box1;
	PhysBody3D* box1body;
	Cube box2;
	PhysBody3D* box2body;
	Cylinder cyl1;
	PhysBody3D* cyl1body;
	Cylinder cyl2;
	PhysBody3D* cyl2body;
	Cylinder cyl3;
	PhysBody3D* cyl3body;
	Cube ramp1;
	PhysBody3D* ramp1body;
	Cube ramp2;
	PhysBody3D* ramp2body;
	Cube ramp3;
	PhysBody3D* ramp3body;
	Cube ramp4;
	PhysBody3D* ramp4body;
	Cube stand1;
	PhysBody3D* stand1body;
	Cube c3;
	PhysBody3D* c3body;
	Cube bridge1;
	PhysBody3D* bridge1body;
};
