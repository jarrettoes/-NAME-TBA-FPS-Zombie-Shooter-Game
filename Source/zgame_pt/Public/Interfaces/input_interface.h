// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "input_interface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class Uinput_interface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ZGAME_PT_API Iinput_interface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual void add_input(ACharacter* target_character) {}; //to connect input to the a character across various files 
	
};
