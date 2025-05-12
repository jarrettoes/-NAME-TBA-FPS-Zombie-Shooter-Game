// Fill out your copyright notice in the Description page of Project Settings.

/*
* 
*  the base character file is used to handle any basic character functitons within the game
*
*	spawning,
*	dying,
*	health functionality,
*	overlapping,
*	etc
* 
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "base_character.generated.h"

class UInputMappingContext;
class UInputAction;
class Uplayable_camera_fp;

USTRUCT()
struct Fhealth_data
{	
	GENERATED_BODY()

	float max_health;
	float current_health; 
};


UCLASS()
class ZGAME_PT_API Abase_character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	Abase_character();

	bool check_vitalStatus() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void drain_health(float& curr_health, float changed_health);
	virtual void regain_health(float& heal_amount);

	
	UFUNCTION()
	virtual void onTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual AActor* Spawn(FName character_name, TSubclassOf<AActor> character); //function to handle spawning 

	virtual void Die(); //function to handle dying

protected:

	virtual void move_action(const FInputActionValue& value);
	virtual void look_action(const FInputActionValue& value);
	virtual void jump_action(); 
	virtual void crouch_initaite();
	virtual void crouch_disengage();
	virtual void Attack_melee();
	virtual void throw_attack(); 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

	bool m_isDead;
		

	Fhealth_data health_data;
		
	
};
