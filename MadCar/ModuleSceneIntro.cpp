#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	c1.size = vec3(100, 10, 100);
	c1.color = Brown;
	c1body = App->physics->AddBody(c1, 0);
	//B1
	b1.size = vec3(5, 5, 5);
	b1.color = Brown;
	b1.SetPos(43, 25, 100);
	b1body = App->physics->AddBody(b1,2);
	//b2
	b2.size = vec3(5, 5, 5);
	b2.color = Brown;
	b2.SetPos(43, 30, 100);
	b2body = App->physics->AddBody(b2, 2);
	//wall 1
	wall1.size = vec3(10, 200, 300);
	wall1.color = Blue;
	wall1.SetPos(55, 100, 150);
	wall1body = App->physics->AddBody(wall1, 0);
	//Light 1
	light1.size = vec3(250, 20, 20);
	light1.SetRotation(30, vec3(0, 0, 1));
	light1.SetPos(50, 50, 10);
	light1.color = LightColor;
	//Light 1
	light2.size = vec3(250, 20, 20);
	light2.SetRotation(30, vec3(0, 0, 1));
	light2.SetPos(50, 50, 100);
	light2.color = LightColor;
	//middle ramp
	ramp1.size = vec3(6, 0.1, 6);
	ramp1.SetRotation(-20, vec3(1,0,0));
	ramp1.SetPos(0, 5.5, 50);
	ramp1.color = Green;
	ramp1body = App->physics->AddBody(ramp1, 0);
	//ramp to stand
	ramp2.size = vec3(15, 0.1, 45);
	ramp2.SetRotation(-30, vec3(1, 0, 0));
	ramp2.SetPos(43, 10,0);
	ramp2.color = Brown;
	ramp2body = App->physics->AddBody(ramp2, 0);
	//ramp to respawn
	ramp3.size = vec3(100, 6.2, 10);
	ramp3.SetRotation(30, vec3(1, 0, 0));
	ramp3.SetPos(0, 0, 52);
	ramp3.color = Brown;
	ramp3body = App->physics->AddBody(ramp3, 0);
	//ramp to stand 2
	ramp4.size = vec3(15, 0.1, 8);
	ramp4.SetRotation(-20, vec3(1, 0, 0));
	ramp4.SetPos(43, 23, 122);
	ramp4.color = SpringGreen;
	ramp4body = App->physics->AddBody(ramp4, 0);
	//stand 1
	stand1.size = vec3(15, 1, 100);
	stand1.SetPos(43, 21, 72);
	stand1.color = Brown;
	stand1body = App->physics->AddBody(stand1, 0);

	//stand 2
	c3.size = vec3(15, 1, 70);
	c3.SetPos(43, 21, 190);
	c3.color = Brown;
	c3body = App->physics->AddBody(c3, 0);
	//Box1
	box1.size = vec3(30, 15, 70);
	box1.SetPos(0, 0, 120);
	box1.color = SpringGreen;
	box1body = App->physics->AddBody(box1, 0);
	//Box2
	box2.size = vec3(20, 15, 100);
	box2.SetPos(-30, 0, 240);
	box2.color = DarkBlue;
	box2body = App->physics->AddBody(box2, 0);
	cyl1.radius = 2;
	cyl1.height = 20;
	cyl1.SetPos(-30, 7.5, 235);
	cyl1.color = SpringGreen;
	cyl1body = App->physics->AddBody(cyl1, 0);
	cyl2.radius = 2;
	cyl2.height = 20;
	cyl2.SetPos(-30, 8, 240);
	cyl2.color = Red;
	cyl2body = App->physics->AddBody(cyl2, 0);
	cyl3.radius = 2;
	cyl3.height = 20;
	cyl3.SetPos(-30, 7.5, 250);
	cyl3.color = SpringGreen;
	cyl3body = App->physics->AddBody(cyl3, 0);
	//bridge 1
	bridge1.size = vec3(10, 0.2, 50);
	bridge1.SetPos(-20, 7.6, 170);
	bridge1.SetRotation(-20, vec3(0, 1, 0));
	bridge1.color = Brown;
	bridge1body = App->physics->AddBody(bridge1, 0);
	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	//p.axis = true;
	//p.Render();
	
	c1.Render();
	wall1.Render();
	
	ramp1.Render();
	ramp2.Render();
	ramp3.Render();
	ramp4.Render();
	stand1.Render();
	c3.Render();
	box1.Render();
	box2.Render();
	cyl1.Render();
	cyl2.Render();
	cyl3.Render();
	bridge1.Render();
	//Render lights
	light1.Render();
	light2.Render();
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

