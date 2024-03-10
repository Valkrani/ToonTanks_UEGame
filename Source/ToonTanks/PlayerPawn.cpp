// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "MySaveGameSystem.h"
#include "PlayerDisplay.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
    PlayerControllerPointer = Cast<APlayerController>(GetController());
    
    if (TurretType == 1)
    {
        FireRate = 2.f;
    }
    else if (TurretType == 2)
    {
        FireRate = 0.5f;
    }
    else
    {
        FireRate = 1.f;
    }

}

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

    TurretType = static_cast<uint8>(ETankTurretTypes::BaseTurret);
    BodyType = static_cast<uint8>(ETankBodyTypes::BaseBody);

    bCanFire = true;

}

void APlayerPawn::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bPlayerAlive = false;
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerPawn::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerPawn::Turn);
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APlayerPawn::Fire);
}

void APlayerPawn::Move(float Input)
{
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    FVector DeltaLocation(0.f);
    DeltaLocation.X = (Input * Speed) * DeltaTime;
    AddActorLocalOffset(DeltaLocation, true);
}

void APlayerPawn::Turn(float Input)
{
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    FRotator DeltaRotation(0.f);
    DeltaRotation.Yaw = (Input * TurnSpeed) * DeltaTime;
    AddActorLocalRotation(DeltaRotation, true);
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (PlayerControllerPointer)
    {
        FHitResult HitResult;
        PlayerControllerPointer->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
        RotateTurret(HitResult.ImpactPoint);
    }
}

void APlayerPawn::Fire()
{
    SetPlayerDisplayPointer();
    if (bCanFire)
    {
        Super::Fire();

        if (LastFiredProjectile)
        {
            if (TurretType == 2)
            {
                LastFiredProjectile->UpdateDamage(20);
            }
            else if (TurretType == 1)
            {
                LastFiredProjectile->SetActorRelativeScale3D(FVector(2,2,2));
                LastFiredProjectile->OwnerType = TurretType;
            }
        }
        GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &APlayerPawn::ResetFireCooldown, FireRate, false);
        bCanFire = false;
        UpdateShootStatusIcon();
    }
}

void APlayerPawn::ResetFireCooldown()
{
    bCanFire = true;
    UpdateShootStatusIcon();
}

void APlayerPawn::SetPlayerTankType(uint8 _TurretType, uint8 _BodyType)
{
    TurretType = _TurretType;
    BodyType = _BodyType;
}

void APlayerPawn::UpdateShootStatusIcon()
{
    UE_LOG(LogTemp, Warning, TEXT("Updating Icon"));
    if (PlayerDisplay)
    {
        UE_LOG(LogTemp, Warning, TEXT("Updating Icon: SUCCESS"));
	    PlayerDisplay->UpdateShootStatusIcon(bCanFire);
    }
}

void APlayerPawn::SetPlayerDisplayPointer()
{
	TArray<UUserWidget*> FoundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UPlayerDisplay::StaticClass());
	for (UUserWidget* FoundWidget : FoundWidgets)
    {
        PlayerDisplay = Cast<UPlayerDisplay>(FoundWidget);
        if (PlayerDisplay)
        {
            UpdateShootStatusIcon();
            break;
        }
    }
}
