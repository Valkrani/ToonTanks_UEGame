// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGameSystem.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UMySaveGameSystem : public USaveGame
{
	GENERATED_BODY()
	
public:
	UMySaveGameSystem();

    UFUNCTION(BlueprintCallable, Category = "SaveGameData")
    void SavePlayerData(FString PlayerName, uint8 _PlayerBodyType, uint8 _PlayerTurretType);
    UFUNCTION(BlueprintCallable, Category = "SaveGameData")
    void LoadPlayerData(FString& OutPlayerName, uint8& OutPlayerBodyType, uint8& OutPlayerTurretType);

	// Your data variables to be saved
    UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
    FString PlayerName;

    UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
    uint8 PlayerBodyType;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
    uint8 PlayerTurretType;
};
