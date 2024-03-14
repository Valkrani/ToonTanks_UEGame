// Fill out your copyright notice in the Description page of Project Settings.


#include "APlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "MySaveGameSystem.h"
#include "PlayerDisplay.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


// Called every frame
void AAPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (PlayerControllerPointer)
    {
        FHitResult HitResult;
        PlayerControllerPointer->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
        RotateTurret(HitResult.ImpactPoint);
    }
}

// Called when the game starts or when spawned
void AAPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
    PlayerControllerPointer = Cast<APlayerController>(GetController());
    
    if (TurretType == 1)
    {
        FireRate = 1.5f;
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
AAPlayerCharacter::AAPlayerCharacter()
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

void AAPlayerCharacter::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bPlayerAlive = false;
}

// Called to bind functionality to input
void AAPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AAPlayerCharacter::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AAPlayerCharacter::Turn);
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AAPlayerCharacter::Fire);
}

void AAPlayerCharacter::Move(float Input)
{
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    FVector DeltaLocation(0.f);
    DeltaLocation.X = (Input * Speed) * DeltaTime;
    AddActorLocalOffset(DeltaLocation);
}

void AAPlayerCharacter::Turn(float Input)
{
    AddControllerYawInput(Input * TurnSpeed * GetWorld()->GetDeltaSeconds());
}

void AAPlayerCharacter::Fire()
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
        GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AAPlayerCharacter::ResetFireCooldown, FireRate, false);
        bCanFire = false;
        UpdateShootStatusIcon();
    }
}

void AAPlayerCharacter::ResetFireCooldown()
{
    bCanFire = true;
    UpdateShootStatusIcon();
}

void AAPlayerCharacter::SetPlayerTankType(uint8 _TurretType, uint8 _BodyType)
{
    TurretType = _TurretType;
    BodyType = _BodyType;
}

void AAPlayerCharacter::UpdateShootStatusIcon()
{
    if (PlayerDisplay)
    {
	    PlayerDisplay->UpdateShootStatusIcon(bCanFire);
    }
}

void AAPlayerCharacter::SetPlayerDisplayPointer()
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
