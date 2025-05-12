// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "character_movementComp.generated.h"


constexpr float DEFAULT_CROUCH_TRANS = 0.5f;
constexpr float DEFAULT_UNCROUCH_TRANS = 0.2f;


/**
 *  custom character movement
 */
UCLASS()
class ZGAME_PT_API Ucharacter_movementComp : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:

	Ucharacter_movementComp();

	virtual void InitializeComponent() override;
	virtual void OnRegister() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void Crouch(bool bClientSimulation = false) override;
	virtual void UnCrouch(bool bClientSimulation = false) override;
	virtual void CalcVelocity(float DeltaTime, float Friction, bool bFluid, float BrakingDeceleration) override;
	void CalcFriction(float velocity, float DeltaTime); 
	virtual void PhysWalking(float DeltaTime, int32 Iterations) override;
	virtual void PhysFalling(float DeltaTime, int32 Iterations) override;


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "movement: CROUCHING")
	bool b_canCrouch;

private:
/*speeds depending on the current movement status*/
	float m_walkSpeed;

	float m_runSpeed;
	float m_sprintSpeed;

	float m_crouchSpeed;

	
private:


	
};
