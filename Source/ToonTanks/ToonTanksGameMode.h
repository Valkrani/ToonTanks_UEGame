// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void ActorKilled(AActor* KilledActor);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame(bool bIsMainMenu);

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

	UFUNCTION(BlueprintCallable)
	int GetTowersAliveCount();

private:
	class AAPlayerCharacter* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;
	APlayerController* PlayerController;

	float StartDelay = 3.f;

	bool IfLevelMainMenu();
	void HandleGameStart();

	int TowersAlive = 0;
	int CountTowersAlive();

	UPROPERTY(BlueprintReadWrite, Category = "Player Types", meta = (AllowPrivateAccess = "true"))
	uint8 PlayerBodyType;
	UPROPERTY(BlueprintReadWrite, Category = "Player Types", meta = (AllowPrivateAccess = "true"))
	uint8 PlayerTurretType;
};
