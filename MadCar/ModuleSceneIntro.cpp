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
update_status ModuleSceneIntro::PreUpdate(float dt)
{
	p2List_item<PhysBody3D*>* temp = sensors.getFirst();
	p2List_item<Cylinder>* temp2 = sensorsR.getFirst();
	for (temp; temp != nullptr ; temp = temp->next )
	{
		if (temp != nullptr && temp2 != nullptr)
		{
			if (temp->data->Coin == true)
			{
				
				App->physics->DestroyBody(*temp->data);
				sensorsR.del(temp2);

				
			}
		}
		
	}
	
	
	return UPDATE_CONTINUE;
}
// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	//start
	CoinSound = App->audio->LoadFx("MUSIC/FlipSound.wav");
	App->audio->PlayMusic("MUSIC/NotMarioKart.ogg");
	//Hinge
	base.size = vec3(1, 20, 1);
	base.SetPos(-30, 14, 260);
	base.color = Red;
	basebody = App->physics->AddBody(base, 12);
	swing.size = vec3(1, 1, 1);
	swing.SetPos(-30, 14, 261);
	swingbody = App->physics->AddBody(swing, 0); 
	btVector3 vec(0, 0.5, 0);
	//Hinge = new btHingeConstraint(*basebody->GetBody(), *swingbody->GetBody(), btVector3(0, 0.5, 0), btVector3(0, 0.5, 0), btVector3(0, 1, 0), btVector3(0, 1, 0));
	Hinge = App->physics->Add_Constraint_Hinge(*basebody, *swingbody, vec3(0, 0, 0.5), vec3(0, 0, -0.5), vec3(0, 0, 1), vec3(0, 0, 1));
	Hinge->enableAngularMotor(true, 4, 500);
	
	//COINS
	Coin1.height = 1;
	Coin1.radius = 2;
	Coin1.SetPos(0, 10, 0);
	Coin1.color = Gold;
	Coin1Body = App->physics->AddBody(Coin1,0);
	Coin1Body->SetAsSensor(true);
	Coin1Body->collision_listeners.add(this);
	sensors.add(Coin1Body);
	sensorsR.add(Coin1);
	//COINS
	c1.size = vec3(100, 10, 100);
	c1.color = Brown;
	c1body = App->physics->AddBody(c1, 0);
	bed.size = vec3(101, 50, 300);
	bed.SetPos(0, -25, 150);
	bed.color =Indigo;
	bedbody = App->physics->AddBody(bed, 0);
	//plane -1
	p2.size = vec3(1000, 10, 1000);
	p2.SetPos(0,-50,0);
	p2.color = Brown;
	//b1
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
	wall1.size = vec3(10, 300,800);
	wall1.color = Blue;
	wall1.SetPos(55, 100, 150);
	wall1body = App->physics->AddBody(wall1, 0);
	//Light 1
	light1.size = vec3(350, 20, 0);
	light1.SetRotation(30, vec3(0, 0, 1));
	light1.SetPos(50, 50, 200);
	light1.color = LightColor;
	//Light 1
	light2.size = vec3(350, 20, 0);
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
	ramp2.color = Glass;
	ramp2body = App->physics->AddBody(ramp2, 0);
	//ramp to respawn
	ramp3.size = vec3(100, 6.2, 10);
	ramp3.SetRotation(30, vec3(1, 0, 0));
	ramp3.SetPos(0, -0.2, 52.9);
	ramp3.color = Brown;
	ramp3body = App->physics->AddBody(ramp3, 0);
	//ramp to stand 2
	ramp4.size = vec3(15, 0.1, 45);
	ramp4.SetRotation(-30, vec3(1, 0, 0));
	ramp4.SetPos(43, 32, 142);
	ramp4.color = Glass;
	ramp4body = App->physics->AddBody(ramp4, 0);
	//ramp to secret room 
	ramp5.size = vec3(15, 0.1, 45);
	ramp5.SetRotation(-30, vec3(1, 0, 0));
	ramp5.SetPos(43, 65, 295);
	ramp5.color = Glass;
	ramp5body = App->physics->AddBody(ramp5, 0);
	//stand 1
	stand1.size = vec3(15, 1, 100);
	stand1.SetPos(43, 21, 72);
	stand1.color = Brown;
	stand1body = App->physics->AddBody(stand1, 0);

	//stand 2
	c3.size = vec3(15, 1, 70);
	c3.SetPos(43, 55, 250);
	c3.color = Brown;
	c3body = App->physics->AddBody(c3, 0);
	//Stand 3
	stand3.size = vec3(15, 6, 50);
	stand3.SetPos(43, 80, 405);
	stand3.color = Brown;
	stand3body = App->physics->AddBody(stand3, 0);
	//SECRET ROOM
	InvWall.size = vec3(100, 500, 1);
	InvWall.SetPos(0, 74, 415);
	InvWall.color = Invisible;
	g1.size = vec3(100, 20, 90);
	g1.SetPos(0, 73, 475);
	g1.color = Brown;
	g1body = App->physics->AddBody(g1, 0);
	BWall.size = vec3(800, 300, 10);
	BWall.SetPos(0, 100, 500);
	BWall.color = Blue;
	BWallbody = App->physics->AddBody(BWall, 0);
	
	//
	//Box1
	box1.size = vec3(30, 15, 70);
	box1.SetPos(0, 0, 120);
	box1.color = SpringGreen;
	box1body = App->physics->AddBody(box1, 0);
	//Box2
	box2.size = vec3(20, 15, 50);
	box2.SetPos(-30, 0, 220);
	box2.color = DarkBlue;
	box2body = App->physics->AddBody(box2, 0);
	cyl1.radius = 2;
	cyl1.height = 20;
	cyl1.SetPos(-30, 7.5, 250);
	cyl1.color = SpringGreen;
	cyl1body = App->physics->AddBody(cyl1, 0);
	cyl2.radius = 2;
	cyl2.height = 20;
	cyl2.SetPos(-30, 8, 265);
	cyl2.color = SpringGreen;
	cyl2body = App->physics->AddBody(cyl2, 0);
	cyl3.radius = 2;
	cyl3.height = 20;
	cyl3.SetPos(-30, 7.5, 280);
	cyl3.color = SpringGreen;
	cyl3body = App->physics->AddBody(cyl3, 0);
	//bridge 1
	bridge1.size = vec3(10, 0.2, 50);
	bridge1.SetPos(-20, 7.6, 170);
	bridge1.SetRotation(-20, vec3(0, 1, 0));
	bridge1.color = Glass;
	bridge1body = App->physics->AddBody(bridge1, 0);
	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));
	//Table 2
	Table1.size = vec3(100, 10, 80);
	Table1.SetPos(0, 0, 320);
	Table1.color = Brown;
	Table1body = App->physics->AddBody(Table1, 0);
	Table2.size = vec3(50, 30, 120);
	Table2.SetPos(25, 20, 340);
	Table2.color = Brown;
	Table2body = App->physics->AddBody(Table2, 0);
	//Wallride
	w1.size = vec3(100, 6, 6);
	w1.SetRotation(-10, vec3(1, 0, 0));
	w1.SetPos(0, 2.7, 360);
	w1.color = Brown;
	w1body = App->physics->AddBody(w1, 0);
	w2.size = vec3(100, 6, 6);
	w2.SetRotation(-20, vec3(1, 0, 0));
	w2.SetPos(0, 4, 365);
	w2.color = Brown;
	w2body = App->physics->AddBody(w2, 0);
	w3.size = vec3(100, 6, 6);
	w3.SetRotation(-30, vec3(1, 0, 0));
	w3.SetPos(0, 6.4, 370);
	w3.color = Brown;
	w3body = App->physics->AddBody(w3, 0);
	w4.size = vec3(100, 6, 6);
	w4.SetRotation(-40, vec3(1, 0, 0));
	w4.SetPos(0, 9.7, 375);
	w4.color = Brown;
	w4body = App->physics->AddBody(w4, 0);
	w5.size = vec3(100, 6, 6);
	w5.SetRotation(-50, vec3(1, 0, 0));
	w5.SetPos(0, 14, 380);
	w5.color = Brown;
	w5body = App->physics->AddBody(w5, 0);
	w6.size = vec3(100, 6, 6);
	w6.SetRotation(-60, vec3(1, 0, 0));
	w6.SetPos(0, 19, 384);
	w6.color = Brown;
	w5body = App->physics->AddBody(w6, 0);
	w7.size = vec3(100, 6, 6);
	w7.SetRotation(-70, vec3(1, 0, 0));
	w7.SetPos(0, 25, 387);
	w7.color = Brown;
	w7body = App->physics->AddBody(w7, 0);
	w8.size = vec3(100, 6, 6);
	w8.SetRotation(-80, vec3(1, 0, 0));
	w8.SetPos(0, 29, 388);
	w8.color = Brown;
	w8body = App->physics->AddBody(w8, 0);
	//Wallride 2
	/*
	w1D.size = vec3(50, 6, 6);
	w1D.SetRotation(-10, vec3(1, 0, 0));
	w1D.SetPos(25, 32.7, 360);
	w1D.color = Brown;
	w1Dbody = App->physics->AddBody(w1D, 0);
	w2D.size = vec3(50, 6, 6);
	w2D.SetRotation(-20, vec3(1, 0, 0));
	w2D.SetPos(25, 34, 365);
	w2D.color = Brown;
	w2Dbody = App->physics->AddBody(w2D, 0);
	w3D.size = vec3(50, 6, 6);
	w3D.SetRotation(-30, vec3(1, 0, 0));
	w3D.SetPos(25, 36.5, 370);
	w3D.color = Brown;
	w3Dbody = App->physics->AddBody(w3D, 0);
	w4D.size = vec3(50, 6, 6);
	w4D.SetRotation(-40, vec3(1, 0, 0));
	w4D.SetPos(25, 39.7, 375);
	w4D.color = Brown;
	w4body = App->physics->AddBody(w4D, 0);
	w5D.size = vec3(50, 6, 6);
	w5D.SetRotation(-50, vec3(1, 0, 0));
	w5D.SetPos(25, 44, 380);
	w5D.color = Brown;
	w5Dbody = App->physics->AddBody(w5D, 0);
	w6D.size = vec3(50, 6, 6);
	w6D.SetRotation(-60, vec3(1, 0, 0));
	w6D.SetPos(25, 49, 383);
	w6D.color = Brown;
	w5body = App->physics->AddBody(w6D, 0);
	w7D.size = vec3(50, 6, 6);
	w7D.SetRotation(-70, vec3(1, 0, 0));
	w7D.SetPos(25, 55, 385);
	w7D.color = Brown;
	w7Dbody = App->physics->AddBody(w7D, 0);
	w8D.size = vec3(50, 6, 6);
	w8D.SetRotation(-80, vec3(1, 0, 0));
	w8D.SetPos(25, 59, 386);
	w8D.color = Brown;
	w8Dbody = App->physics->AddBody(w8D, 0);*/
	//FWALL
	FWall.size = vec3(100, 6, 50);
	FWall.SetRotation(-80, vec3(1, 0, 0));
	FWall.SetPos(0, 49, 391);
	FWall.color = Brown;
	FWallbody = App->physics->AddBody(FWall, 0);
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
	//Hinge
	
	basebody->GetTransform(&base.transform);
	base.Render();
	swing.Render();
	//p.axis = true;
	p2.Render();
	BWall.Render();
	c1.Render();
	wall1.Render();
	InvWall.Render();
	g1.Render();
	
	stand1.Render();
	c3.Render();
	box1.Render();
	box2.Render();
	cyl1.Render();
	cyl2.Render();
	cyl3.Render();
	bridge1.Render();
	Table1.Render();
	Table2.Render();
	bed.Render();
	stand3.Render();
	//wallride
	w1.Render();
	w2.Render();
	w3.Render();
	w4.Render();
	w5.Render();
	w6.Render();
	w7.Render();
	w8.Render();
	w1D.Render();
	w2D.Render();
	w3D.Render();
	w4D.Render();
	w5D.Render();
	w6D.Render();
	w7D.Render();
	w8D.Render();
	FWall.Render();
	
	
	p2List_item<Cylinder>* temp2 = sensorsR.getFirst();
	for (temp2; temp2 != nullptr; temp2 = temp2->next)
	{
		if (temp2->data.color.b <1|| temp2->data.color.r <1 || temp2->data.color.g <1)
		{
			//App->audio->PlayFx(CoinSound);
			temp1.Set(temp2->data.color.r + 0.01, temp2->data.color.g + 0.01, temp2->data.color.b +0.01);
			temp2->data.color = temp1;

					}
		else
		{
			//temp1.Set(0,1,0);
			temp1.Set(temp2->data.color.r - 0.81, temp2->data.color.g -0.81, temp2->data.color.b - 0.81);
			temp2->data.color = temp1;
		}
		//temp2->data.color = temp1;
		temp2->data.Render();
	}
	

	
	//Coin1.Render();
	//Render lights
	btVector3 pos = App->player->GetVehiclePosition();
	
	ramp1.Render();

	ramp3.Render();
	ramp4.Render();
	ramp5.Render();
	
	light2.Render();
	light1.Render();
	bridge1.Render();
	ramp2.Render();
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (Coin1Body == body2 || Coin1Body == body1)
	{
     		body1->Coin = true;
			App->audio->PlayFx(CoinSound);
	}
	
}

