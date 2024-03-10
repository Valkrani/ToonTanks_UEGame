// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerDisplay.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UPlayerDisplay : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdatePlayerStatsDisplay(float UpdatedHealth, float UpdatedArmor);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthAndArmorDisplayText(float NewHealthDisplay, float NewArmorDisplay);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateShootStatusIcon(bool CanShoot);
};
