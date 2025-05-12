// Fill out your copyright notice in the Description page of Project Settings.


#include "health_bar.h"

Uhealth_bar::Uhealth_bar(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	
}

void Uhealth_bar::NativeConstruct()
{
	Super::NativeConstruct();
}

void Uhealth_bar::draw_healthBar(float currentHealth, float maxHealth)
{
	m_health_bar->SetPercent(currentHealth / maxHealth);
}
