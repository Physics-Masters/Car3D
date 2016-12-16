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
	
	//middle ramp
	ramp1.size = vec3(6, 0.1, 2);
	ramp1.SetRotation(-30, vec3(1,0,0));
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
	ramp3.size = vec3(100, 6.5, 10);
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
	c3.SetPos(43, 21, 170);
	c3.color = Brown;
	c3body = App->physics->AddBody(c3, 0);





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
	light1.Render();
	ramp1.Render();
	ramp2.Render();
	ramp3.Render();
	ramp4.Render();
	stand1.Render();
	c3.Render();
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

