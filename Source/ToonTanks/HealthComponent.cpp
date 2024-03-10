// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerPawn.h"
#include "TowerPawn.h"
#include "ToonTanksGameMode.h"
#include "PlayerDisplay.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UHealthComponent::IsArmored()
{
	if (GetOwner()->GetInstigatorController()->IsPlayerController())
	{
		// check player type if is armor type
		APlayerPawn* Tank = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
		if (Tank)
		{
			if (Tank->GetBodyType() == 1)
			{
				return true;
			}
		}
	}
	else
	{
		// check tower type if is armor type
		ATowerPawn* Tower = Cast<ATowerPawn>(GetOwner());
		if (Tower)
		{
			if (Tower ->GetTowerType() == 1)
			{
				return true;
			}
		}
	}

	return false;
}

bool UHealthComponent::IsAntiArmor(AController* Instigator)
{
	if (Instigator)
	{
		APlayerPawn* PlayerPawn = Cast<APlayerPawn>(Instigator->GetPawn());
        ATowerPawn* TowerPawn = Cast<ATowerPawn>(Instigator->GetPawn());

        if (PlayerPawn && PlayerPawn->GetTurretType() == 1)
        {
            return true;
        }
        else if (TowerPawn && TowerPawn->GetTowerType() == 3)
        {
            return true;
        }	
	}
	
	return false;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	// Check if the owner is the player or a turret
	// then set the armor according to the Enum type
	if (IsArmored())
	{
		CurrentArmor = MaxArmor;
	}

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
} 

void UHealthComponent::SetPlayerDisplayPointer()
{

	TArray<UUserWidget*> FoundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UPlayerDisplay::StaticClass());
	for (UUserWidget* FoundWidget : FoundWidgets)
    {
        PlayerDisplay = Cast<UPlayerDisplay>(FoundWidget);
        if (PlayerDisplay)
        {
			PlayerDisplay->UpdatePlayerStatsDisplay(CurrentHealth, CurrentArmor);
            break;
        }
    }
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0.f)
		return;

	if (IsAntiArmor(Instigator))
	{
		CurrentArmor -= Damage;
		CurrentHealth -= Damage;
	}
	else
	{
		CurrentArmor -= Damage;
		if (CurrentArmor < 0.f)
		{
			CurrentHealth += CurrentArmor;
		}
	}
	if (CurrentArmor < 0.f)
	{
		CurrentArmor = 0.f;
	}

	// if (CurrentArmor > 0)
	// {
	// 	float DamageOld = Damage;
	// 	Damage -= CurrentArmor;
	// 	CurrentArmor -= DamageOld;
	// }
	// CurrentHealth -= Damage;

	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (DamagedActor == PlayerPawn)
	{
		SetPlayerDisplayPointer();
		if (PlayerDisplay)
		{
			PlayerDisplay->UpdatePlayerStatsDisplay(CurrentHealth, CurrentArmor);
		}	
	}

	if (CurrentHealth <= 0.f && ToonTanksGameMode)
	{
		ToonTanksGameMode->ActorKilled(DamagedActor);
	}
}