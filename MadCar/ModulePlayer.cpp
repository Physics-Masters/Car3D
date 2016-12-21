#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"
#include "ModulePhysics3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
	vehiclestate = GROUND;
	gameplaytimer = PLAYING_TIME;
	score = 0;
	endflip = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;
	
	// Car properties ----------------------------------------
	car.num_chassis = 7;
	car.chassis_size = new vec3[car.num_chassis];
	car.chassis_size[0].Set(0.75f, 0.5f, 4.25f);
	car.chassis_size[1].Set(0.3f, 1, 0.1f);
	car.chassis_size[2].Set(1, 0.8f, 1.5f);
	car.chassis_size[3].Set(1.8f, 0.25f, 0.25f);
	car.chassis_size[4].Set(1.5f, 0.15f, 0.15f);
	car.chassis_size[5].Set(2, 0.1f, 0.35f);
	car.chassis_size[6].Set(1.5f, 0.35f, 1.85f);

	
	car.chassis_offset = new vec3[car.num_chassis];
	car.chassis_offset[0].Set(0, 0.5f, 0);
	car.chassis_offset[1].Set(0, 1.0f, -2.25f);
	car.chassis_offset[2].Set(0, 0.75f, -0.9f);
	car.chassis_offset[3].Set(0, 0.65f, -2.1f);
	car.chassis_offset[4].Set(0, 0.5f, 2);
	car.chassis_offset[5].Set(0, 1.5f, -2.25f);
	car.chassis_offset[6].Set(0, 0.6f, -0.6f);
	
	car.chassis_color = new vec3[car.num_chassis];
	car.chassis_color[0] = { Blue.r, Blue.g, Blue.b };
	car.chassis_color[1] = { Gold.r, Gold.g, Gold.b };//Gold;
	car.chassis_color[2] = { Blue.r, Blue.g, Blue.b };// Blue;
	car.chassis_color[3] = { Gold.r, Gold.g, Gold.b };// Gold;
	car.chassis_color[4] = { Black.r, Black.g, Black.b };//Black;
	car.chassis_color[5] = { Black.r, Black.g, Black.b };//Black;
	car.chassis_color[6] = { Gold.r, Gold.g, Gold.b };//Gold;

	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;
	

	// Wheel properties ---------------------------------------
	float connection_height = 0.5f;
	float wheel_radius = 0.5f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 0.5f;

	// Don't change anything below this line ------------------

	float half_width = 3*0.5f;
	float half_length = 5*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);

	
	vehicle->SetPos(0.0f, 12.0f, 10.0f);
	
	

	originalpos = new float[16];
	vehicle->GetTransform(originalpos);

	play = READY;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	delete originalpos;

	return true;
}

 btVector3 ModulePlayer::GetVehiclePosition()
{
	 return vehicle->vehicle->getRigidBody()->getWorldTransform().getOrigin();
}

 void ModulePlayer::GameProgress()
 {
	 if (play == READY)
	 {
		 if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
		 {
			 play = PLAYING;
			 time.Start();
		 }
	 }
	 if (play == PLAYING)
	 {
		 gameplaytimer = PLAYING_TIME - time.Read()/1000.0f;
		 if (gameplaytimer < 0)
		 {
			 play = END;
			 time.Stop();
		 }
	 }
	 if (play == END)
	 {
		if(vehicle->GetKmh() > 1 || vehicle->GetKmh() < -1)
		vehicle->Brake(BRAKE_POWER);
		if(App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)// && vehicle->GetKmh() < 2.0f && vehicle->GetKmh() > -2.0f)
			Reset();
	 }
 }

 void ModulePlayer::Reset()
 {
	 // Reset game;
	 vehicle->SetTransform(originalpos);
	 play = READY;	 
	 gameplaytimer = PLAYING_TIME;
	 score = 0;
	 endflip = 0.0;
	 vehicle->GetBody()->setLinearVelocity({ 0.0f, 0.0f, 0.0f });
	 vehicle->GetBody()->setAngularVelocity({ 0.0f, 0.0f, 0.0f });
	
 }

 void ModulePlayer::Move()
 {
	 turn = acceleration = brake = 0.0f;
	 
	
	 if (play == PLAYING)
	 {
			
		 bool vehicleonground = CheckVehicleCollision(Y.x, Y.y, Y.z);
		 if (vehicleonground == true && vehiclestate != GROUND)
		 {
			 vehiclestate = GROUND;
		 }
		 else if (vehicleonground == false && vehiclestate == GROUND)
		 {
			 vehiclestate = AIR;
		 }
		
		 //turbo
		 int t;
		 if (App->input->GetKey(SDL_SCANCODE_T) == KEY_REPEAT)
		 {
			 t = 2;
		 }
		 else t = 1;

		 //brake and go forward
		 if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && vehicle->GetKmh() < 0)
		 {
			 brake = BRAKE_POWER;
		 }
		 else if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		 {
			 acceleration = t*MAX_ACCELERATION;
		 }

		 //brake and go backwards
		 if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && vehicle->GetKmh() > 0)
		 {
			 brake = BRAKE_POWER;
		 }
		 else if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		 {
			 acceleration = -MAX_ACCELERATION;
		 }

		 //turn left
		 if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		 {
			 if (turn < TURN_DEGREES)
				 turn += TURN_DEGREES;
		 }
		 
		 //turn right
		 if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		 {
			 if (turn > -TURN_DEGREES)
				 turn -= TURN_DEGREES;
		 }
	
		 //jump
		 if ((App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && vehiclestate == GROUND))
		 {
			 vehiclestate = AIR;
			 vehicle->Push(0, 10 * vehicle->info.mass, 0);
		 }
	 }	
	 
	 //Shake car
	 if (vehiclestate == GROUND)
	 {
		 if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
			 vehicle->flip(X.x, X.y, X.z);
		 if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
			 vehicle->flip(-X.x, -X.y, -X.z);
		 if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
			 vehicle->flip(Z.x / 2, Z.y / 2, Z.z / 2);
		 if (App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN)
			 vehicle->flip(-Z.x / 2, -Z.y / 2, -Z.z / 2);
	 }

	 vehicle->ApplyEngineForce(acceleration);
	 vehicle->Turn(turn);
	 vehicle->Brake(brake);

 }

 void ModulePlayer::Flips()
 {
	 if (vehiclestate != GROUND) {
		 if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && vehiclestate != FRONTFLIP)
		 {
			 if (vehiclestate == BACKFLIP)
			 {
				 vehiclestate = AIR;
				 vehicle->flip(X.x, X.y, X.z);
			 }
			 else
			 {
				 vehiclestate = FRONTFLIP;
				 vehicle->flip(1.5* X.x, 1.5 * X.y, 1.5 * X.z);
				 fliptimer.Start();
			 }
		 }
		 if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN  && vehiclestate != BACKFLIP)
		 {
			 if (vehiclestate == FRONTFLIP)
			 {
				 vehiclestate = AIR;
				 vehicle->flip(-1.5*X.x, -1.5*X.y, -1.5*X.z);
			 }
			 else
			 {
				 vehiclestate = BACKFLIP;
				 vehicle->flip(-X.x, -X.y, -X.z);
				 fliptimer.Start();
			 }
		 }

		 if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN && vehiclestate != TURNRIGHT)
		 {
			 if (vehiclestate == TURNLEFT)
				 vehiclestate = AIR;
			 else vehiclestate = TURNRIGHT;

			 vehicle->flip(1.5*Y.x, 1.5*Y.y, 1.5*Y.z);
			 fliptimer.Start();
		 }
		 if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN && vehiclestate != TURNLEFT)
		 {
			 if (vehiclestate == TURNRIGHT)
				 vehiclestate = AIR;
			 else vehiclestate = TURNLEFT;
			 vehicle->flip(-1.5*Y.x, -1.5*Y.y, -1.5*Y.z);
			 fliptimer.Start();
		 }

		 if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN && vehiclestate != RIGHTFLIP)
		 {
			 if (vehiclestate == LEFTFLIP)
				 vehiclestate = AIR;
			 else vehiclestate = RIGHTFLIP;
			 vehicle->flip(Z.x / 3, Z.y / 3, Z.z / 3);
			 fliptimer.Start();
		 }
		 if (App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN && vehiclestate != LEFTFLIP)
		 {
			 if (vehiclestate == RIGHTFLIP)
				 vehiclestate = AIR;
			 else vehiclestate = LEFTFLIP;
			 vehicle->flip(-Z.x / 3, -Z.y / 3, -Z.z / 3);
			 fliptimer.Start();
		 }
		 if (vehiclestate != AIR)
		 {
			 endflip = (float)fliptimer.Read() / 1000.0f;
		 }
	 }
 }

 void ModulePlayer::Score()
 {
	
	
	 if (vehiclestate == FRONTFLIP && endflip >= FRONTFLIP_TIME)
	 {
		 score += 200;
		 fliptimer.Stop();
		 vehiclestate = AIR;
		 vehicle->flip(-1.5*X.x, -1.5*X.y, -1.5*X.z);
	 }
	 if (vehiclestate == BACKFLIP && endflip >= BACKFLIP_TIME)
	 {
		 score += 200;
		 fliptimer.Stop();
		 vehiclestate = AIR;
		 vehicle->flip(X.x, X.y, X.z);
	 }
	 if (vehiclestate == LEFTFLIP || vehiclestate == RIGHTFLIP)
	 {
		 if (endflip >= SIDEFLIP_TIME)
		 {
			 score += 200;
			 fliptimer.Stop();
			 if (vehiclestate == LEFTFLIP)
				 vehicle->flip(Z.x / 3, Z.y / 3, Z.z / 3);
			 else  vehicle->flip(-Z.x / 3, -Z.y / 3, -Z.z / 3);
			 vehiclestate = AIR;
			
		 }
	 }
	 if (vehiclestate == TURNRIGHT || vehiclestate == TURNLEFT)
	 {
		 if (endflip >= TURNSIDE_TIME)
		 {
			 score += 200;
			 fliptimer.Stop();
			 if (vehiclestate == TURNRIGHT)
				 vehicle->flip(-1.5*Y.x, -1.5*Y.y, -1.5*Y.z);
			 else vehicle->flip(1.5*Y.x, 1.5*Y.y, 1.5*Y.z);
			 vehiclestate = AIR;
			
		 }
	 }
 }

 bool ModulePlayer::CheckVehicleCollision(float x, float y, float z)
 {
	 for (int i = 0; i < vehicle->info.num_wheels; ++i)
	 {
		 
		 btVector3 btFrom = vehicle->vehicle->getWheelTransformWS(i).getOrigin();
		 btVector3 btTo = { btFrom.getX() - x, btFrom.getY() - y, btFrom.getZ() - z };
		 btCollisionWorld::ClosestRayResultCallback res(btFrom, btTo);
		 App->physics->GetWorld()->rayTest(btFrom, btTo, res);

		 if (res.hasHit() == true)
		 {
			 return true;
		 }
	 }
	 for (int i = 0; i < vehicle->info.num_wheels; ++i)
	 {

		 btVector3 btFrom = vehicle->vehicle->getWheelTransformWS(i).getOrigin();
		 btVector3 btTo = { btFrom.getX() +2*x, btFrom.getY() +2*y, btFrom.getZ() +2*z };
		 btCollisionWorld::ClosestRayResultCallback res(btFrom, btTo);
		 App->physics->GetWorld()->rayTest(btFrom, btTo, res);

		 if (res.hasHit() == true)
		 {
			 return true;
		 }
	 }
	
	 return false;
 }

// Update: draw background
 update_status ModulePlayer::Update(float dt)
 {
	 GameProgress();

	 vehicle->GetTransform(&vehicle_transf);

	 X = { vehicle_transf[0],vehicle_transf[1],vehicle_transf[2] };
	 Y = { vehicle_transf[4],vehicle_transf[5],vehicle_transf[6] };
	 Z = { vehicle_transf[8],vehicle_transf[9],vehicle_transf[10] };

	 //Car can move
	 Move();
		
	 Flips();

	 Score();

	 vehicle->Render();
	 
	 char title[80];
	 int min = (int) gameplaytimer / 60;
	 float sec = gameplaytimer - min * 60;
	 sprintf_s(title, "%.1f Km/h Timer: %d:%.2f m:s Score %d", vehicle->GetKmh(), min, sec, score);
	 App->window->SetTitle(title);

	 return UPDATE_CONTINUE;
 }



