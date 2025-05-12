// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "health_bar.h"
#include "Components/WidgetComponent.h"
#include "in_game_hud.generated.h"

/**
 * 
 */
UCLASS()
class ZGAME_PT_API Ain_game_hud : public AHUD
{
	GENERATED_BODY()
	
public:

	Ain_game_hud();	


	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

	void DisplayHealthUI(float curr_health, float m_health);

	UPROPERTY(EditDefaultsOnly, Category = "health hud")
	TSubclassOf<UUserWidget> health_bar_class;

private:	
	class Uhealth_bar* health_bar_widget;
	
};
