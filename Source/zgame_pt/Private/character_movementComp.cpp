// Fill out your copyright notice in the Description page of Project Settings.


#include "character_movementComp.h"

Ucharacter_movementComp::Ucharacter_movementComp()
{
	AirControl = 1.0f;
	AirControlBoostMultiplier = 0.0f;
	AirControlBoostVelocityThreshold = 0.0f;
	MaxAcceleration = 600.0f;
	
}

void Ucharacter_movementComp::InitializeComponent()
{

}

void Ucharacter_movementComp::OnRegister()
{

}

void Ucharacter_movementComp::Crouch(bool bClientSimulation)
{

}

void Ucharacter_movementComp::UnCrouch(bool bClientSimulation)
{

}

void Ucharacter_movementComp::CalcVelocity(float DeltaTime, float Friction, bool bFluid, float BrakingDeceleration)
{
	
}

void Ucharacter_movementComp::CalcFriction(float velocity, float DeltaTime)
{
	
}

void Ucharacter_movementComp::PhysWalking(float DeltaTime, int32 Iterations)
{
}

void Ucharacter_movementComp::PhysFalling(float DeltaTime, int32 Iterations)
{
}

void Ucharacter_movementComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
