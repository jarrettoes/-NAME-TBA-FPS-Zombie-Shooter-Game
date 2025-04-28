// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/base_character.h"
#include "Camera/playable_camera_fp.h"
#include "Components/CapsuleComponent.h"
#include "Player/basic_locomotion.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values
Abase_character::Abase_character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(35.f, 96.0f); 

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> main_mesh (TEXT("SkeletalMesh'/Game/characters/meshes/Y_Bot.Y_Bot'"));
	if (main_mesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(main_mesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	}
	
	main_camera = CreateDefaultSubobject<Uplayable_camera_fp>(TEXT("FP Camera"));
	main_camera->SetupAttachment(GetCapsuleComponent());
	main_camera->SetRelativeLocation(FVector(20.0f, 0.0f, 80.0f));
	main_camera->bUsePawnControlRotation = true;

	locomotion_comp = CreateDefaultSubobject<Ubasic_locomotion>(TEXT("locomotion component"));

	AutoPossessPlayer = EAutoReceiveInput::Player1;

	GetCharacterMovement()->GroundFriction = 8.0f;
	GetCharacterMovement()->BrakingFrictionFactor = 0.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2048.0f;
	GetCharacterMovement()->GravityScale = 1.0;
}

// Called when the game starts or when spawned
void Abase_character::BeginPlay()
{
	Super::BeginPlay();

	Controller->Possess(this);

	locomotion_comp->add_input(this);
	main_camera->add_input(this); 

}

// Called every frame
void Abase_character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void Abase_character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

