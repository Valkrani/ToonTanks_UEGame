// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "APlayerCharacter.h"
#include "TowerPawn.h"
#include "ToonTanksPlayerController.h"
#include "MySaveGameSystem.h"
#include "Camera/CameraActor.h"

bool AToonTanksGameMode::IfLevelMainMenu()
{
    FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
    FString MainMenuLevelName = TEXT("MainMenu");

    if (CurrentLevelName.Equals(MainMenuLevelName))
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}

void AToonTanksGameMode::ActorKilled(AActor* KilledActor)
{
    if (KilledActor == Tank)
    {
        Tank->HandleDestruction();
        if (ToonTanksPlayerController && Tank)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }
        GameOver(false);
    }
    else if (ATowerPawn* DestroyedTower = Cast<ATowerPawn>(KilledActor))
    {
        DestroyedTower->HandleDestruction();
        TowersAlive--;
        if (TowersAlive == 0)
        {
            GameOver(true);
        }
    }
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();
}

int AToonTanksGameMode::GetTowersAliveCount()
{
    return TowersAlive;
}

void AToonTanksGameMode::HandleGameStart()
{
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    Tank = Cast<AAPlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
    if (IfLevelMainMenu())
    {
        ToonTanksPlayerController->ChangePlayerCameraMainMenu();

        Tank->SetActorHiddenInGame(true);
        Tank->SetActorTickEnabled(false);
        ToonTanksPlayerController->SetPlayerEnabledState(false);
        StartGame(true);
        return;
    }
    TowersAlive = CountTowersAlive();

    FString PlayerName;
    UMySaveGameSystem* SaveGameSystem = NewObject<UMySaveGameSystem>();
    SaveGameSystem->LoadPlayerData(PlayerName, PlayerBodyType, PlayerTurretType);
    Tank->SetPlayerTankType(PlayerTurretType, PlayerBodyType);

    StartGame(false);

    if (ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnabledState(false);

        FTimerHandle StartTimerHandle;
        FTimerDelegate StartTimerDelegate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController,
            &AToonTanksPlayerController::SetPlayerEnabledState,
            true);
        GetWorldTimerManager().SetTimer(
            StartTimerHandle,
            StartTimerDelegate,
            StartDelay,
            false
        );
    }
}

int AToonTanksGameMode::CountTowersAlive()
{
    TArray<AActor*> TowersArray;
    UGameplayStatics::GetAllActorsOfClass(this, ATowerPawn::StaticClass(), TowersArray);
    return TowersArray.Num();
}