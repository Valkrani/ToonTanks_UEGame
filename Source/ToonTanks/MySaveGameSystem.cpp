// Fill out your copyright notice in the Description page of Project Settings.


#include "MySaveGameSystem.h"
#include "Kismet/GameplayStatics.h"

UMySaveGameSystem::UMySaveGameSystem()
{
    PlayerName = TEXT("Player 0");
    PlayerBodyType = 0;
    PlayerTurretType = 0;
}

void UMySaveGameSystem::SavePlayerData(FString _PlayerName, uint8 _PlayerBodyType, uint8 _PlayerTurretType)
{
    UMySaveGameSystem* SaveGameInstance = Cast<UMySaveGameSystem>(UGameplayStatics::CreateSaveGameObject(UMySaveGameSystem::StaticClass()));
    SaveGameInstance->PlayerName = _PlayerName;
    SaveGameInstance->PlayerBodyType = _PlayerBodyType;
    SaveGameInstance->PlayerTurretType = _PlayerTurretType;
    UGameplayStatics::SaveGameToSlot(SaveGameInstance, "MySaveSlot", 0);
}

void UMySaveGameSystem::LoadPlayerData(FString& OutPlayerName, uint8& OutPlayerBodyType, uint8& OutPlayerTurretType)
{
    UMySaveGameSystem* LoadedSaveGame = Cast<UMySaveGameSystem>(UGameplayStatics::LoadGameFromSlot("MySaveSlot", 0));
    if (LoadedSaveGame)
    {
        OutPlayerName = LoadedSaveGame->PlayerName;
        OutPlayerBodyType = LoadedSaveGame->PlayerBodyType;
        OutPlayerTurretType = LoadedSaveGame->PlayerTurretType;
    }
    else
    {
        OutPlayerName = PlayerName;
        OutPlayerBodyType = PlayerBodyType;
        OutPlayerTurretType = PlayerTurretType;
    }
}