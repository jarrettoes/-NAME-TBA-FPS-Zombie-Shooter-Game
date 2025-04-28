// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "main_gameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ZGAME_PT_API Amain_gameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	Amain_gameModeBase();

protected:

	virtual void BeginPlay() override;
	
};
