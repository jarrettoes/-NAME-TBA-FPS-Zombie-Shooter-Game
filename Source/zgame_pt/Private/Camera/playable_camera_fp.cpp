// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/playable_camera_fp.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include <EnhancedInputSubsystems.h>
#include "GameFramework/CharacterMovementComponent.h"

Uplayable_camera_fp::Uplayable_camera_fp()
{

}

void Uplayable_camera_fp::BeginPlay()
{
	Super::BeginPlay();

	character_ref = Cast<ACharacter>(GetOwner());
	if(!character_ref)
	UE_LOG (LogTemp, Warning, TEXT("character_ref is null"));
	if(character_ref)
		player_controller = Cast<APlayerController>(character_ref->GetController());
	if(!player_controller)
	UE_LOG (LogTemp, Warning, TEXT("player_controller is null"));
}

void Uplayable_camera_fp::look_mouse(const FInputActionValue& value)
{
	m_look_amount_mouse = value.Get<FVector2D>();
	if (player_controller)
	{
		if(m_look_amount_mouse.X != 0.0f) character_ref->AddControllerYawInput(m_look_amount_mouse.X);
		if(m_look_amount_mouse.Y != 0.0f) character_ref->AddControllerPitchInput(m_look_amount_mouse.Y);
	}
}

void Uplayable_camera_fp::look_controller(const FInputActionValue& value)
{
	m_look_amount_controller = value.Get<FVector2D>();

	if (player_controller)
	{
		if(m_look_amount_controller.X != 0.0f) character_ref->AddControllerYawInput(m_look_amount_controller.X * 45.f * GetWorld()->GetDeltaSeconds()); 
		if(m_look_amount_controller.Y != 0.0f) character_ref->AddControllerPitchInput(m_look_amount_controller.Y * 45.f * GetWorld()->GetDeltaSeconds()); 
	}
}

void Uplayable_camera_fp::add_input(ACharacter* target_character)
{
	character_ref = target_character;

	player_controller = Cast<APlayerController>(character_ref->GetController()); 
	if (player_controller)
	{
		UEnhancedInputLocalPlayerSubsystem* Enhanced_subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(player_controller->GetLocalPlayer());
		Enhanced_subsys->AddMappingContext(camera_controlls_mappings, 0);

		if (UEnhancedInputComponent* E_Input = CastChecked<UEnhancedInputComponent>(player_controller->InputComponent))
		{
			E_Input->BindAction(look_mouse_input, ETriggerEvent::Triggered, this, &Uplayable_camera_fp::look_mouse);
			E_Input->BindAction(look_controller_input, ETriggerEvent::Triggered, this, &Uplayable_camera_fp::look_controller); 
		}
	}
}

void Uplayable_camera_fp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction); 

		
}
