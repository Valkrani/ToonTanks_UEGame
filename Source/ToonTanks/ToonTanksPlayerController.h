// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ToonTanksPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AToonTanksPlayerController();
	void SetPlayerEnabledState(bool bPlayerEnabled);

	UFUNCTION(BlueprintCallable, Category = "Player Camera Controls")
	void ChangePlayerCameraMainMenu();
	UFUNCTION(BlueprintCallable, Category = "Player Camera Controls")
	void ChangePlayerCameraCustomize();

private:
	TArray<AActor*> CameraPositions;
};