// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class TOONTANKS_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();
	
	void HandleDestruction();

protected:
	void RotateTurret(FVector RotateTarget);
	void Fire();

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	float FireRate;
	FTimerHandle FireRateTimerHandle;

	class AProjectile* LastFiredProjectile;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Pawn Components");
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class USoundBase* DeathSound;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;
};
