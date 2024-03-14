// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerPawn.h"
#include "APlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Projectile.h"


bool ATowerPawn::IsPlayerInRange() const
{
    if (PlayerTank)
    {
        float PlayerDistance = FVector::Dist(GetActorLocation(), PlayerTank->GetActorLocation());
        if (PlayerDistance <= FireRange)
        {
            return true;
        }
    }

    return false;
}

void ATowerPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

        if (IsPlayerInRange())
        {
            RotateTurret(PlayerTank->GetActorLocation());
        }
}

void ATowerPawn::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

// Called when the game starts or when spawned
void ATowerPawn::BeginPlay()
{
    Super::BeginPlay();

    if (TowerType == 2)
    {
        FireRate = 0.7f;
    }
    else if (TowerType == 3)
    {
        FireRate = 2.3f;
    }
    else
    {
        FireRate = 1.2f;
    }

    PlayerTank = Cast<AAPlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATowerPawn::CheckFireCondition, FireRate, true);
}

void ATowerPawn::CheckFireCondition()
{
    if (IsPlayerInRange() && PlayerTank->bPlayerAlive)
    {
        Fire();
    }
}


void ATowerPawn::Fire()
{
    Super::Fire();
    if (LastFiredProjectile)
    {
        if (TowerType == 2)
        {
            LastFiredProjectile->UpdateDamage(20);
        }
        else if (TowerType == 3)
        {
            LastFiredProjectile->SetActorRelativeScale3D(FVector(2,2,2));
            LastFiredProjectile->OwnerType = TowerType;
        }
    }
}