// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "playable_camera_fp.generated.h"

class ACharacter;
class APlayerController;
class UInputAction;
class UInputMappingContext;

UCLASS()
class ZGAME_PT_API Uplayable_camera_fp : public UCameraComponent
{
	GENERATED_BODY()
	
public:

	Uplayable_camera_fp();

protected:

	virtual void BeginPlay() override;
	
	/*for camera functionality. Looking around and such*/	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:

	class ACharacter* basic_character;
	class Aplayer_character* player_character;
	
};
