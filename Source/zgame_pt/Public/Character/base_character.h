// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "base_character.generated.h"

class Ubasic_locomotion;
class Uplayable_camera_fp;

UCLASS()
class ZGAME_PT_API Abase_character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	Abase_character();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	USkeletalMesh* character_mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "camera")
	Uplayable_camera_fp* main_camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	Ubasic_locomotion* locomotion_comp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	
	
};
