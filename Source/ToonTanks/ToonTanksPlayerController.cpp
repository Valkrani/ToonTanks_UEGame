// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraActor.h"

AToonTanksPlayerController::AToonTanksPlayerController()
{
    TSubclassOf<AActor> CameraActorClass = ACameraActor::StaticClass();
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), CameraActorClass, CameraPositions);
}

void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
    if (bPlayerEnabled)
    {
        GetPawn()->EnableInput(this);
    }
    else
    {
        GetPawn()->DisableInput(this);
    }
    bShowMouseCursor = bPlayerEnabled;
}

void AToonTanksPlayerController::ChangePlayerCameraMainMenu()
{
        SetViewTargetWithBlend(CameraPositions[0], 0.4f);
}
void AToonTanksPlayerController::ChangePlayerCameraCustomize()
{
        SetViewTargetWithBlend(CameraPositions[1], 0.4f);
}