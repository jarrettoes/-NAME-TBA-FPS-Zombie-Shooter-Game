// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/main_gameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Pawn.h"

Amain_gameModeBase::Amain_gameModeBase()
: Super()
{
	static ConstructorHelpers::FClassFinder<APawn> base_char (TEXT("/Game/characters/Mybase_character")); 
	if (base_char.Succeeded())
	{
		DefaultPawnClass = base_char.Class; 
	}
	
}

void Amain_gameModeBase::BeginPlay()
{
	Super::BeginPlay();
}
