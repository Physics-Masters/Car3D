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
/*	p2List_item<PhysBody3D*>* temp = sensors.getFirst();
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
	
	*/
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
	Coin1.SetPos(0, 7, 0);
	Coin1.color = Gold;
	Coin1.SetRotation(90, vec3(0, 1, 0));
	Coin1Body = App->physics->AddBody(Coin1,0);
	Coin1Body->SetAsSensor(true);
	Coin1Body->collision_listeners.add(this);
	sensors.add(Coin1Body);
	sensorsR.add(Coin1);
	Coin2.height = 1;
	Coin2.radius = 2;
	Coin2.SetRotation(90, vec3(0, 1, 0));
	Coin2.SetPos(-120, 2, 170);
	Coin2.color = Gold;
	Coin2Body = App->physics->AddBody(Coin2, 0);
	Coin2Body->SetAsSensor(true);
	Coin2Body->collision_listeners.add(this);
	sensors.add(Coin2Body);
	sensorsR.add(Coin2);
	Coin3.height = 1;
	Coin3.radius = 2;
	Coin3.SetPos(0, 9.5, 120);
	Coin3.SetRotation(90, vec3(0, 1, 0));
	Coin3.color = Gold;
	Coin3Body = App->physics->AddBody(Coin3, 0);
	Coin3Body->SetAsSensor(true);
	Coin3Body->collision_listeners.add(this);
	sensors.add(Coin3Body);
	sensorsR.add(Coin3);
	Coin4.height = 1;
	Coin4.radius = 2;
	Coin4.SetPos(-30, 7, 300);
	Coin4.SetRotation(90, vec3(0, 1, 0));
	Coin4.color = Gold;
	Coin4Body = App->physics->AddBody(Coin4, 0);
	Coin4Body->SetAsSensor(true);
	Coin4Body->collision_listeners.add(this);
	sensors.add(Coin4Body);
	sensorsR.add(Coin4);
	Coin5.height = 1;
	Coin5.radius = 2;
	Coin5.SetPos(30, 37, 300);
	Coin5.SetRotation(90, vec3(0, 1, 0));
	Coin5.color = Gold;
	Coin5Body = App->physics->AddBody(Coin5, 0);
	Coin5Body->SetAsSensor(true);
	Coin5Body->collision_listeners.add(this);
	sensors.add(Coin5Body);
	sensorsR.add(Coin5);
	Coin6.height = 2;
	Coin6.radius = 2;
	Coin6.SetPos(43, 24, 72);
	Coin6.SetRotation(90, vec3(0, 1, 0));
	Coin6.color = Gold;
	Coin6Body = App->physics->AddBody(Coin6, 0);
	Coin6Body->SetAsSensor(true);
	Coin6Body->collision_listeners.add(this);
	sensors.add(Coin6Body);
	sensorsR.add(Coin6);
	Coin7.height = 2;
	Coin7.radius = 2;
	Coin7.SetPos(43, 58, 250);
	Coin7.SetRotation(90, vec3(0, 1, 0));
	Coin7.color = Gold;
	Coin7Body = App->physics->AddBody(Coin7, 0);
	Coin7Body->SetAsSensor(true);
	Coin7Body->collision_listeners.add(this);
	sensors.add(Coin7Body);
	sensorsR.add(Coin7);
	Coin8.height = 2;
	Coin8.radius = 2;
	Coin8.SetPos(43, 85, 405);
	Coin8.SetRotation(90, vec3(0, 1, 0));
	Coin8.color = Gold;
	Coin8Body = App->physics->AddBody(Coin8, 0);
	Coin8Body->SetAsSensor(true);
	Coin8Body->collision_listeners.add(this);
	sensors.add(Coin8Body);
	sensorsR.add(Coin8);
	Coin9.height = 1;
	Coin9.radius = 2;
	Coin9.SetPos(0, 85, 475);
	Coin9.SetRotation(90, vec3(0, 1, 0));
	Coin9.color = Gold;
	Coin9Body = App->physics->AddBody(Coin9, 0);
	Coin9Body->SetAsSensor(true);
	Coin9Body->collision_listeners.add(this);
	sensors.add(Coin9Body);
	sensorsR.add(Coin9);
	Coin10.height = 1;
	Coin10.radius = 2;
	Coin10.SetPos(-10, 85, 475);
	Coin10.SetRotation(90, vec3(0, 1, 0));
	Coin10.color = Gold;
	Coin10Body = App->physics->AddBody(Coin10, 0);
	Coin10Body->SetAsSensor(true);
	Coin10Body->collision_listeners.add(this);
	sensors.add(Coin10Body);
	sensorsR.add(Coin10);
	//COINS
	//TOP
	
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
	b1.color = Glass;
	b1.SetPos(43, 25, 100);
	b1body = App->physics->AddBody(b1,2);
	//b2
	b2.size = vec3(5, 5, 5);
	b2.color = Glass;
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
	InvWall.size = vec3(150, 500, 1);
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
	FWall.SetPos(0, 49, 391.1);
	FWall.color = Brown;
	FWallbody = App->physics->AddBody(FWall, 0);
	Top.size = vec3(100, 10, 50);
	Top.SetPos(0, 72, 415);
	Top.color = Brown;
	topbody = App->physics->AddBody(Top, 0);
	//
	//2nd part of the level
	bed2.size = vec3(101, 50, 250);
	bed2.SetPos(-100, -40, 170);
	bed2.color = Indigo;
	bed2body = App->physics->AddBody(bed2, 0);
	//box 3
	box3.size = vec3(70, 15, 30);
	box3.SetPos(-100, -7.5, 120);
	box3.color = SpringGreen;
	box3body = App->physics->AddBody(box3, 0);
	//box 4
	box4.size = vec3(30, 15, 30);
	box4.SetPos(-120, -7.5, 170);
	box4.color = SpringGreen;
	box4body = App->physics->AddBody(box4, 0);
	//box 5
	box5.size = vec3(70, 15, 30);
	box5.SetPos(-100, -7.5, 220);
	box5.color = SpringGreen;
	box5body = App->physics->AddBody(box5, 0);
	//box 6
	box6.size = vec3(25, 25, 15);
	box6.SetPos(-50, -17.775, 170);
	box6.SetRotation(-45, vec3(0, 0, 1));
	box6.color = SpringGreen;
	box6body = App->physics->AddBody(box6, 0);
	//hinge1
	//Hinge
	base1.size = vec3(1, 25, 1);
	base1.SetPos(-120, 0, 140);
	base1.color = Red;
	base1body = App->physics->AddBody(base1, 50);
	swing1.size = vec3(1, 1, 1);
	swing1.SetPos(-120, 0, 141);
	swing1body = App->physics->AddBody(swing1, 0);
	Hinge1 = App->physics->Add_Constraint_Hinge(*base1body, *swing1body, vec3(0, 0, 0.5), vec3(0, 0, -0.5), vec3(0, 0, 1), vec3(0, 0, 1));
	Hinge1->enableAngularMotor(true, 4, 500);
	//Hinge
	base2.size = vec3(1, 25, 1);
	base2.SetPos(-120, 0, 200);
	base2.color = Red;
	base2body = App->physics->AddBody(base2, 50);
	swing2.size = vec3(1, 1, 1);
	swing2.SetPos(-120, 0, 201);
	swing2body = App->physics->AddBody(swing2, 0);
	Hinge2 = App->physics->Add_Constraint_Hinge(*base2body, *swing2body, vec3(0, 0, 0.5), vec3(0, 0, -0.5), vec3(0, 0, 1), vec3(0, 0, 1));
	Hinge2->enableAngularMotor(true, 4, 500);
	//limits
	Cube l1,l2, l3, l4, l5,l6;
	l1.size = vec3(2, 100, 100);
	l1.SetPos(-50, 50, 0);
	l1body = App->physics->AddBody(l1, 0);
	l2.size = vec3(2, 200, 250);
	l2.SetPos(-50, 100, 405);
	l2body = App->physics->AddBody(l2, 0);
	l3.size = vec3(100, 200, 2);
	l3.SetPos(-100, 50, 280);
	l3body = App->physics->AddBody(l3, 0);
	l4.size = vec3(100, 200, 2);
	l4.SetPos(-100, 50, 50);
	l4body = App->physics->AddBody(l4, 0);
	l5.size = vec3(100, 200, 2);
	l5.SetPos(0, 50, -50);
	l5body = App->physics->AddBody(l5, 0);
	l6.size = vec3(2, 200, 250);
	l6.SetPos(-150, 75, 160);
	l6body = App->physics->AddBody(l6, 0);
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
	//Plane p(0, 1, 0, 0);
	//Hinge
	
	basebody->GetTransform(&base.transform);
	base.Render();
	swing.Render();
	//p.axis = true;
	b1body->GetTransform(&b1.transform);
	b1.Render();
	b2body->GetTransform(&b2.transform);
	b2.Render();
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
	Top.Render();
	
	p2List_item<Cylinder>* temp2 = sensorsR.getFirst();
	p2List_item<PhysBody3D*>* temp3 = sensors.getFirst();
	for (temp2; temp2 != nullptr; temp2 = temp2->next)
	{
		if (temp3->data->Coin == false)
		{
			if (temp2->data.color.b < 1 || temp2->data.color.r < 1 || temp2->data.color.g < 1)
			{
				//App->audio->PlayFx(CoinSound);
				temp1.Set(temp2->data.color.r + 0.01, temp2->data.color.g + 0.01, temp2->data.color.b + 0.01);
				temp2->data.color = temp1;

			}
			else
			{
				//temp1.Set(0,1,0);
				temp1.Set(temp2->data.color.r - 0.81, temp2->data.color.g - 0.81, temp2->data.color.b - 0.81);
				temp2->data.color = temp1;
			}
			//temp2->data.color = temp1;
			temp2->data.Render();
		}
		temp3 = temp3->next;
	}
	

	
	//Coin1.Render();
	//Second part
	bed2.Render();
	box3.Render();
	box4.Render();
	box5.Render();
	box6.Render();
	base1body->GetTransform(&base1.transform);
	base1.Render();
	swing1.Render();
	base2body->GetTransform(&base2.transform);
	base2.Render();
	swing2.Render();
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
	p2List_item<PhysBody3D*>* temp = sensors.getFirst();
	for (; temp != nullptr; temp = temp->next)
	{
		if ((temp->data == body1 && temp->data->Coin == false) || (temp->data == body2 && temp->data->Coin == false))
		{
			temp->data->Coin = true;
			App->player->score += 2000;
			App->player->coins--;
			App->audio->PlayFx(CoinSound);
		}
	}
}

void ModuleSceneIntro::SensorsReset()
{
	p2List_item<PhysBody3D*>* temp = sensors.getFirst();
	for (; temp != nullptr; temp = temp->next)
	{
			temp->data->Coin = false;
	}
}

