// Fill out your copyright notice in the Description page of Project Settings.


#include "main_gameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "in_game_hud.h"
#include "GameFramework/Pawn.h"

Amain_gameModeBase::Amain_gameModeBase()
: Super()
{
	static ConstructorHelpers::FClassFinder<APawn> base_char (TEXT("/Game/characters/Myplayer_character")); 
	if (base_char.Succeeded())
	{
		DefaultPawnClass = base_char.Class; 
	}

	static ConstructorHelpers::FClassFinder<AHUD> gameplay_hud (TEXT("/Game/UI/gameplay_hud"));
	if (gameplay_hud.Succeeded())
	{
		HUDClass = gameplay_hud.Class;
	}
}

void Amain_gameModeBase::BeginPlay()
{
	Super::BeginPlay();
}
