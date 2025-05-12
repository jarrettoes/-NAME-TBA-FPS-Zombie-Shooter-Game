// Fill out your copyright notice in the Description page of Project Settings.


#include "base_character.h"
#include "playable_camera_fp.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
Abase_character::Abase_character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(35.f, 96.0f);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &Abase_character::OnOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &Abase_character::OnOverlapEnd);

	m_isDead = false;
}

// Called when the game starts or when spawned
void Abase_character::BeginPlay()
{
	Super::BeginPlay();
	Owner->OnTakeAnyDamage.AddDynamic(this, &Abase_character::onTakeAnyDamage);
}

void Abase_character::drain_health(float& curr_health, float changed_health)
{
	curr_health = FMath::Clamp(curr_health - changed_health, 0.0f, health_data.max_health);
}

void Abase_character::regain_health(float& heal_amount)
{
	if (health_data.current_health < health_data.max_health)
	{
		health_data.current_health = FMath::Clamp(health_data.current_health + heal_amount, 0.0f, health_data.max_health);
	}
}	

void Abase_character::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
#if UE_BUILD_DEVELOPMENT
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.0f, FColor::Green, FString::Printf(TEXT("overlap has begun!")));
#endif // UE_BUILD_DEVELOPMENT

		drain_health(health_data.current_health, 10);

	}
}

void Abase_character::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
#if UE_BUILD_DEVELOPMENT
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.0f, FColor::Red, FString::Printf(TEXT("overlap has begun!")));
#endif // UE_BUILD_DEVELOPMENT
	}
}

void Abase_character::onTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
#if UE_BUILD_DEVELOPMENT
	UE_LOG (LogTemp, Warning, TEXT("we're taking damage!"));
#endif // UE_BUILD_DEVELOPMENT

	drain_health(health_data.current_health, 10);

	if (health_data.current_health <= 0.0f)
	{
		Die(); //will implement the die function
	}
}


AActor* Abase_character::Spawn(FName character_name, TSubclassOf<AActor> character)
{
	UWorld* world = GetWorld();
	if (!world || !character)
	{
		UE_LOG(LogTemp, Warning, TEXT("Either the world or the character is null")); 
		return nullptr;
	}

	if (world)
	{
		const FRotator spawn_rotation = FRotator::ZeroRotator;
		const FVector spawn_location = FVector::ZeroVector;

		FActorSpawnParameters spawn_character_info;
		spawn_character_info.Name = character_name;
		spawn_character_info.Owner = this;
		spawn_character_info.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		AActor* spawned_character = world->SpawnActor<AActor>(character, spawn_location, spawn_rotation, spawn_character_info);
		
		return spawned_character;
	}
	return nullptr;
}

void Abase_character::Die()
{
	APlayerController* possessed_controller = Cast<APlayerController>(GetController());

	if (m_isDead)
	{
		if (possessed_controller)
		{
			possessed_controller->UnPossess();
			this->Destroy();
		}
	}
}

void Abase_character::move_action(const FInputActionValue& value)
{
	FVector2D move_value = value.Get<FVector2D>();

	if(move_value.Y != 0.0f) AddMovementInput(GetActorForwardVector(), move_value.Y);
	if(move_value.X != 0.0f) AddMovementInput(GetActorRightVector(), move_value.X);
}

void Abase_character::look_action(const FInputActionValue& value)
{
	FVector2D look_value = value.Get<FVector2D>(); 
	
	if(look_value.Y != 0.0f) AddControllerPitchInput(look_value.Y);
	if(look_value.X != 0.0f) AddControllerYawInput(look_value.X);
}

void Abase_character::jump_action()
{
	Jump();
}

void Abase_character::crouch_initaite()
{
	if(GetCharacterMovement()->IsMovingOnGround())
	Crouch();
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void Abase_character::crouch_disengage()
{
	UnCrouch();
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}


void Abase_character::Attack_melee()
{

}

void Abase_character::throw_attack()
{

}

// Called every frame
void Abase_character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


bool Abase_character::check_vitalStatus() const
{
#if UE_BUILD_DEVELOPMENT
	if (m_isDead)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.0f, FColor::Red, TEXT("DEAD"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.0f, FColor::Green, TEXT("ALIVE"));
	}
#endif

	return !m_isDead; 
}