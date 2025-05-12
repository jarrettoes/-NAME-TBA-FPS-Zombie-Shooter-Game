// Fill out your copyright notice in the Description page of Project Settings.


#include "in_game_hud.h"

Ain_game_hud::Ain_game_hud()
{

}

void Ain_game_hud::BeginPlay()
{
	Super::BeginPlay();

	if (health_bar_class)
	{
		health_bar_widget = CreateWidget<Uhealth_bar>(GetWorld(), health_bar_class);
		if(health_bar_widget)
			health_bar_widget->AddToViewport();
	}
	
}

void Ain_game_hud::DrawHUD()
{
	Super::DrawHUD();

}

void Ain_game_hud::DisplayHealthUI(float curr_health, float m_health)
{
	if(health_bar_widget)
		health_bar_widget->draw_healthBar(curr_health, m_health);
}
