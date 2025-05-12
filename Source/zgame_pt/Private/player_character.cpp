// Fill out your copyright notice in the Description page of Project Settings.


#include "player_character.h"
#include "playable_camera_fp.h"
#include "base_character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include <EnhancedInputSubsystems.h>
#include "GameFramework/PlayerController.h"
#include "Components/CapsuleComponent.h"
#include "in_game_hud.h"

Aplayer_character::Aplayer_character()
{
	
	/*to communicated with the parent class!*/

	d_health.max_health = 100;
	d_health.current_health = d_health.max_health;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> main_mesh(TEXT("SkeletalMesh'/Game/characters/meshes/Y_Bot.Y_Bot'"));
	if (main_mesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(main_mesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
		GetMesh()->SetupAttachment(RootComponent);
	}

	main_camera_component = CreateDefaultSubobject<Uplayable_camera_fp>(TEXT("main camera")); 
	main_camera_component->SetupAttachment(RootComponent);
	main_camera_component->SetRelativeLocation(FVector(20.0f, 0.0f, 80.0f));
	main_camera_component->bUsePawnControlRotation = true;

	GetCharacterMovement()->JumpZVelocity = 900.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->GravityScale = 4.5f;
	GetCharacterMovement()->GroundFriction = 8.0f; //whats the friction on the ground? (might change if different surfaces come to play)
	GetCharacterMovement()->BrakingDecelerationWalking = 1048;
	GetCharacterMovement()->BrakingFrictionFactor = 0.0f;

	crouching_alpha_time = 0.0f;
	crouch_speed = 4.0f;
	crouch_EyeOffset = FVector::ZeroVector;
	
}


void Aplayer_character::BeginPlay()
{
	Super::BeginPlay();

	player_controller = Cast<APlayerController>(GetController());
	if (player_controller)
	{
		UEnhancedInputLocalPlayerSubsystem* Enhanced_subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(player_controller->GetLocalPlayer());
		Enhanced_subsys->AddMappingContext(player_inputMappings, 0);
	}

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	game_hud = Cast<Ain_game_hud>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (game_hud)
		game_hud->DisplayHealthUI(getCurrentHealth(), getMaxHealth());
}

float Aplayer_character::getCurrentHealth() const
{
	return d_health.current_health;
}

float Aplayer_character::getMaxHealth() const
{
	return d_health.max_health;
}

AActor* Aplayer_character::Spawn(FName character_name, TSubclassOf<AActor> character)
{	
	Super::Spawn(character_name, character);
	/* add some spawn logic for specific areas and respawn vantage points*/
	return Spawn(character_name, character);
}

void Aplayer_character::Die()
{
	Super::Die();
}

void Aplayer_character::move_action(const FInputActionValue& value)
{
	Super::move_action(value);
}

void Aplayer_character::look_action(const FInputActionValue& value)
{
	Super::look_action(value);
}

void Aplayer_character::jump_action()
{
	Super::jump_action();
}

void Aplayer_character::crouch_initaite()
{
	Super::crouch_initaite();
	UE_LOG(LogTemp, Warning, TEXT("we're crouching"));
	m_crouch = true;
}

void Aplayer_character::crouch_disengage()
{
	if (m_crouch)
	{
		Super::crouch_disengage();
		UE_LOG(LogTemp,Warning,TEXT("we're not crouching"));
		m_crouch = false;
	}
}

void Aplayer_character::crouch_interpTransition(float DeltaTime)
{
	if (m_crouch)
	{
		crouching_alpha_time = FMath::Clamp(crouching_alpha_time - DeltaTime * 2.5f, 0.0f, 1.0f);
		float current_halfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		float changed_halfHeight = FMath::InterpEaseIn(GetCapsuleComponent()->GetScaledCapsuleHalfHeight(), 0.0f, crouching_alpha_time, 2.0f);
		GetCapsuleComponent()->SetCapsuleHalfHeight(FMath::Lerp(current_halfHeight, changed_halfHeight, DeltaTime * 15.f));
	}
	if (!m_crouch)
	{
		crouching_alpha_time = FMath::Clamp(crouching_alpha_time - DeltaTime * 2.5f, 0.0f, 1.0f);
		float current_halfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		float changed_halfHeight = FMath::InterpEaseIn(GetCapsuleComponent()->GetScaledCapsuleHalfHeight(), 0.0f, crouching_alpha_time, 2.0f);
		GetCapsuleComponent()->SetCapsuleHalfHeight(FMath::Lerp(current_halfHeight, changed_halfHeight, DeltaTime * 15.f));
	}
}

void Aplayer_character::drain_health(float& curr_health, float changed_health)
{
	Super::drain_health(curr_health, changed_health);
}

void Aplayer_character::regain_health(float& heal_amount)
{
	Super::regain_health(heal_amount);
}

void Aplayer_character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#if UE_BUILD_DEVELOPMENT
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.0f, FColor::Green, FString::Printf(TEXT("HEALTH: %f/%f"), getCurrentHealth(), getMaxHealth()));
#endif // UE_BUILD_DEVELOPMENT

	crouch_interpTransition(DeltaTime);
}

void Aplayer_character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
	if (UEnhancedInputComponent* player_input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		player_input->BindAction(move_input, ETriggerEvent::Triggered, this, &Aplayer_character::move_action);
		player_input->BindAction(look_input, ETriggerEvent::Triggered, this, &Aplayer_character::look_action);
		player_input->BindAction(crouch_input, ETriggerEvent::Started, this, &Aplayer_character::crouch_initaite);
		player_input->BindAction(crouch_input, ETriggerEvent::Completed, this, &Aplayer_character::crouch_disengage);
		player_input->BindAction(jump_input, ETriggerEvent::Triggered, this, &Aplayer_character::jump_action);
	}
}