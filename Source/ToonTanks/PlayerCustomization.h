// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerPawn.h"
#include "PlayerCustomization.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UPlayerCustomization : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SaveGameImplementation(FString PlayerName, uint8 PlayerBodyType, uint8 PlayerTurretType);
};
