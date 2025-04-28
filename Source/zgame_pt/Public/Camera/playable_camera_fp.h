// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "Interfaces/input_interface.h"
#include "playable_camera_fp.generated.h"

class ACharacter;
class APlayerController;
class UInputAction;
class UInputMappingContext;

UCLASS()
class ZGAME_PT_API Uplayable_camera_fp : public UCameraComponent, public Iinput_interface
{
	GENERATED_BODY()
	
public:

	Uplayable_camera_fp();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "input")
	UInputMappingContext* camera_controlls_mappings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "input")
	UInputAction* look_mouse_input;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "input")
	UInputAction* look_controller_input;

	virtual void add_input(ACharacter* target_character) override; 
protected:

	virtual void BeginPlay() override;
		
	/*for camera functionality. Looking around and such*/
	void look_mouse(const FInputActionValue& value);
	void look_controller(const FInputActionValue& value);
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:

	FVector2D m_look_amount_mouse, m_look_amount_controller;

	ACharacter* character_ref;
	APlayerController* player_controller;
	
};
