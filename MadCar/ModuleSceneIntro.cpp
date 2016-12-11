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

	c1.size = vec3(50, 10, 50);
	c1.color = Brown;
	c1body = App->physics->AddBody(c1, 0);

	ramp1.size = vec3(6, 0.1, 2);
	ramp1.SetRotation(-30, vec3(1,0,0));
	ramp1.SetPos(0, 5.5, 25);
	ramp1.color = Green;
	ramp1body = App->physics->AddBody(ramp1, 0);

	ramp2.size = vec3(6, 0.1, 20);
	ramp2.SetRotation(-30, vec3(1, 0, 0));
	ramp2.SetPos(20, 10,0);
	ramp2.color = Brown;
	ramp2body = App->physics->AddBody(ramp2, 0);

	c2.size = vec3(10, 1, 50);
	c2.SetPos(20, 15, 35);
	c2.color = Brown;
	c2body = App->physics->AddBody(c2, 0);

	c3.size = vec3(10, 1, 50);
	c3.SetPos(20, 15, 120);
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
	p.axis = true;
	p.Render();
	c1.Render();
	ramp1.Render();
	ramp2.Render();
	c2.Render();
	c3.Render();
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

