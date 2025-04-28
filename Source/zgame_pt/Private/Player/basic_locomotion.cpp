// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/basic_locomotion.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <EnhancedInputSubsystems.h>

Ubasic_locomotion::Ubasic_locomotion()
{

}

void Ubasic_locomotion::BeginPlay()
{
	Super::BeginPlay();

	player_controller = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)); 
	if(player_controller)
		character_ref = Cast<ACharacter>(player_controller->GetCharacter()); 
	
}

void Ubasic_locomotion::move(const FInputActionValue& move_amount)
{
	m_moveAmount = move_amount.Get<FVector2D>();

	if (player_controller)
	{
		if(m_moveAmount.Y != 0.0f) character_ref->AddMovementInput(character_ref->GetActorForwardVector(), m_moveAmount.Y);
		if(m_moveAmount.X != 0.0f) character_ref->AddMovementInput(character_ref->GetActorRightVector(), m_moveAmount.X);
	
	}
}

void Ubasic_locomotion::jump()
{
}

void Ubasic_locomotion::start_crouch()
{
}

void Ubasic_locomotion::end_crouch()
{
}

void Ubasic_locomotion::add_input(ACharacter* target_character)
{
	character_ref = target_character; 

	player_controller = Cast<APlayerController>(character_ref->GetController()); 
	if (player_controller)
	{
		UEnhancedInputLocalPlayerSubsystem* Enhanced_subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(player_controller->GetLocalPlayer());
		Enhanced_subsys->AddMappingContext(basic_locomotion_mappings, 0);

		if (UEnhancedInputComponent* E_Input = CastChecked<UEnhancedInputComponent>(player_controller->InputComponent))
		{
			E_Input->BindAction(move_input, ETriggerEvent::Triggered, this, &Ubasic_locomotion::move);
		}
	}
}

void Ubasic_locomotion::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector& vel = character_ref->GetCharacterMovement()->Velocity;
	//apply_friction(vel, DeltaTime);

#if UE_BUILD_DEVELOPMENT
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.0f, FColor::Cyan, FString::Printf(TEXT("kinetic friction: %s"), *(GetFriction().ToString())));
#endif // UE_BUILD_DEVELOPMENT

}

FVector Ubasic_locomotion::apply_friction(FVector& velocity, float deltaTime)
{
	/*actions like friction upon the character after we stopped moving*/
	
	//if the velocity is not zero
	if (!velocity.IsNearlyZero())
	{
		FVector Force_k = -velocity.GetSafeNormal() * FRICTION_COEFFICENT;
		
		velocity += Force_k * deltaTime;
	
		float friction_viaFrame = FRICTION_COEFFICENT;
	
	}
	if (character_ref->GetCharacterMovement()->GetLastInputVector().IsNearlyZero() && velocity.IsNearlyZero(0.5))
		velocity = FVector::ZeroVector;
	return velocity; 
}

FVector Ubasic_locomotion::GetFriction()
{
	return character_ref->GetCharacterMovement()->Velocity;
}
