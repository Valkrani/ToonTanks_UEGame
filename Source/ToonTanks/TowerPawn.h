// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "TowerTypesEnum.h"
#include "TowerPawn.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATowerPawn : public ABasePawn
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	uint8 GetTowerType() const { return TowerType; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class APlayerPawn* PlayerTank;

	bool IsPlayerInRange() const;

	UPROPERTY(EditDefaultsOnly, Category="Tower Stats|Turret")
	float FireRange = 800.f;

	void CheckFireCondition();

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Tower Stats", meta = (AllowPrivateAccess = "true"))
	uint8 TowerType = static_cast<uint8>(ETowerTypes::BasicTower);

	void Fire();
};
