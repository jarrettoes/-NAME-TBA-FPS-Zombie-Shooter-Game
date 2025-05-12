// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "health_bar.generated.h"

/**
 * 
 */
UCLASS()
class ZGAME_PT_API Uhealth_bar : public UUserWidget
{
	GENERATED_BODY()

public:

	Uhealth_bar(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override; 
	
	void draw_healthBar(float currentHealth, float maxHealth);


	UPROPERTY(meta = (BindWidget))
	class UProgressBar* m_health_bar;
		
};
