// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCustomization.h"
#include "MySaveGameSystem.h"

void UPlayerCustomization::SaveGameImplementation(FString PlayerName, uint8 PlayerBodyType, uint8 PlayerTurretType)
{
    UMySaveGameSystem* SaveGameSystem = NewObject<UMySaveGameSystem>();
    SaveGameSystem->SavePlayerData(PlayerName, PlayerBodyType, PlayerTurretType);
}