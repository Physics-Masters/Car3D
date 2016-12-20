#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// ----------------------------------------------------------------------------
VehicleInfo::~VehicleInfo()
{
	//if(wheels != NULL)
		//delete wheels;
}

// ----------------------------------------------------------------------------
PhysVehicle3D::PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info) : PhysBody3D(body), vehicle(vehicle), info(info)
{
}

// ----------------------------------------------------------------------------
PhysVehicle3D::~PhysVehicle3D()
{
	delete vehicle;
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Render()
{
	Cylinder wheel;

	wheel.color = Grey;

	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.radius = info.wheels[0].radius;
		wheel.height = info.wheels[0].width;

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

		wheel.Render();
	}
	
	Cube chassis;
	for (int i = 0; i < info.num_chassis; ++i)
	{
		chassis.color.Set(info.chassis_color[i].x, info.chassis_color[i].y, info.chassis_color[i].z);
		chassis.size = { info.chassis_size[i].x, info.chassis_size[i].y, info.chassis_size[i].z };
		vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
		btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
		btVector3 offset(info.chassis_offset[i].x, info.chassis_offset[i].y, info.chassis_offset[i].z);
		offset = offset.rotate(q.getAxis(), q.getAngle());
		
		chassis.transform.M[12] += offset.getX();
		chassis.transform.M[13] += offset.getY();
		chassis.transform.M[14] += offset.getZ();
		
		chassis.Render();
	}
	
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyEngineForce(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Brake(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Turn(float degrees)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].steering == true)
		{
			vehicle->setSteeringValue(degrees, i);
		}
	}
}

// ----------------------------------------------------------------------------
float PhysVehicle3D::GetKmh() const
{
	return vehicle->getCurrentSpeedKmHour();
}



bool PhysVehicle3D::WheelisInContact()
{
	for (int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if (vehicle->getWheelInfo(i).m_raycastInfo.m_isInContact == true)
			return true;
	}
	return false;
}
