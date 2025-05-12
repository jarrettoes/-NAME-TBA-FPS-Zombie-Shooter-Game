// Fill out your copyright notice in the Description page of Project Settings.


#include "playable_camera_fp.h"
#include "GameFramework/Character.h"
#include "player_character.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

Uplayable_camera_fp::Uplayable_camera_fp()
{
	SetFieldOfView(90.f);
	
}

void Uplayable_camera_fp::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* player_controller = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if(player_controller)
		player_character = Cast<Aplayer_character>(player_controller->GetOwner());
}

void Uplayable_camera_fp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction); 

		
}
