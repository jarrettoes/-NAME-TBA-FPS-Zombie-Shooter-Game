// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "Interfaces/input_interface.h"
#include "EnhancedInputComponent.h"
#include "basic_locomotion.generated.h"

#define FRICTION_COEFFICENT 0.2f;

class UInputAction;
class UInputMappingContext;
class ACharacter; 
class APlayerController;

UCLASS()
class ZGAME_PT_API Ubasic_locomotion : public UMovementComponent, public Iinput_interface
{
	GENERATED_BODY()
	
public:

	Ubasic_locomotion(); 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "inputs")
	UInputMappingContext* basic_locomotion_mappings;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "inputs")
	UInputAction* move_input;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "inputs")
	UInputAction* jump_input;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "inputs")
	UInputAction* crouch_input;

	virtual void add_input(ACharacter* target_character) override;

protected:

	virtual void BeginPlay() override;
	
	/*basic locomoiton inputs. Moving, jumping, crouching etc*/
	void move(const FInputActionValue& value);
	void jump(); 
	void start_crouch();
	void end_crouch();

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:

	FVector apply_friction(FVector& velocity, float deltaTime);
	FVector GetFriction();

	FVector2D m_moveAmount;

	ACharacter* character_ref;
	APlayerController* player_controller;
	
};
