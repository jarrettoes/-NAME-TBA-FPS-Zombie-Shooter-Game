// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "base_character.h"
#include "EnhancedInputComponent.h"
#include "player_character.generated.h"

/*
* 
*	the player character file is to handle functionality to playable characters.
*	skeletal meshes.
*	hit boxes, capsule components.
*	initalizing health,
*	etc
*
 */

UCLASS()
class ZGAME_PT_API Aplayer_character : public Abase_character
{
	GENERATED_BODY()
	
public:

	Aplayer_character();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkeletalMesh")
	class USkeletalMesh* character_meshes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class Uplayable_camera_fp* main_camera_component;

	/*for inputs*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "input")
	class UInputMappingContext* player_inputMappings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "input")
	class UInputAction* move_input;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "input")
	class UInputAction* look_input;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "input")
	class UInputAction* jump_input;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "input")
	class UInputAction* crouch_input;
	

	FORCEINLINE float getCurrentHealth() const;
	FORCEINLINE float getMaxHealth() const;
	FORCEINLINE bool check_ifCrouching() const {return m_crouch;}
	FORCEINLINE FVector getCrouchEyeOffset() const {return crouch_EyeOffset;}

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	
	virtual void BeginPlay() override;
	virtual AActor* Spawn(FName character_name, TSubclassOf<AActor> character) override;
	virtual void Die() override;
	virtual void Tick(float DeltaTime) override;

protected:

	virtual void move_action(const FInputActionValue& value) override;
	virtual void look_action(const FInputActionValue& value) override;
	virtual void jump_action() override;
	virtual void crouch_initaite() override;
	virtual void crouch_disengage() override;
	void crouch_interpTransition(float DeltaTime);

private:

	virtual void drain_health(float& curr_health, float changed_health) override;
	virtual void regain_health(float& heal_amount) override;

	bool m_crouch;
	float crouch_speed; 
	float crouching_alpha_time;
	FVector crouch_EyeOffset; 
	Fhealth_data d_health;
	APlayerController* player_controller;
	class Ain_game_hud* game_hud;
};
