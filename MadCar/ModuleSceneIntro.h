#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:
	
	/*PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;*/
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
	Cube Table2;
	PhysBody3D* Table2body;
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
	Cube ramp5;
	PhysBody3D* ramp5body;
	Cube stand1;
	PhysBody3D* stand1body;
	Cube stand3;
	PhysBody3D* stand3body;
	Cube c3;
	PhysBody3D* c3body;
	Cube bridge1;
	PhysBody3D* bridge1body;
	//Secret Room
	Cube g1;
	PhysBody3D*g1body;
	Cube InvWall;
	Cube BWall;
	PhysBody3D*BWallbody;
	Cube p2;
	//Wallride
	Cube w1;
	PhysBody3D* w1body;
	Cube w2;
	PhysBody3D* w2body;
	Cube w3;
	PhysBody3D* w3body;
	Cube w4;
	PhysBody3D* w4body;
	Cube w5;
	PhysBody3D* w5body;
	Cube w6;
	PhysBody3D* w6body;
	Cube w7;
	PhysBody3D* w7body;
	Cube w8;
	PhysBody3D* w8body;
	//wallride2
	Cube w1D;
	PhysBody3D* w1Dbody;
	Cube w2D;
	PhysBody3D* w2Dbody;
	Cube w3D;
	PhysBody3D* w3Dbody;
	Cube w4D;
	PhysBody3D* w4Dbody;
	Cube w5D;
	PhysBody3D* w5Dbody;
	Cube w6D;
	PhysBody3D* w6Dbody;
	Cube w7D;
	PhysBody3D* w7Dbody;
	Cube w8D;
	PhysBody3D* w8Dbody;
	//wall
	Cube FWall;
	PhysBody3D* FWallbody;
	//BEd
	Cube bed;
	PhysBody3D* bedbody;
	//vehicle
//	Cube Vehicle;
//	PhysBody3D* VehicleCollider;
	//sensors
	Cylinder Coin1;
	PhysBody3D* Coin1Body;
	p2List<PhysBody3D*> sensors;
	p2List<Cylinder> sensorsR;
};
