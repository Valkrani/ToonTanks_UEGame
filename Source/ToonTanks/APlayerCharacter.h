// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerTankTypesEnum.h"
#include "APlayerCharacter.generated.h"

UCLASS()
class TOONTANKS_API AAPlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void HandleDestruction();

	APlayerController* GetPlayerController() const {return this->PlayerControllerPointer;}

	UFUNCTION(BlueprintCallable, Category = "Player Body Type")
	void SetPlayerTankType(uint8 _TurretType, uint8 _BodyType);

	bool bPlayerAlive = true;

	uint8 GetTurretType() const { return TurretType; }
	uint8 GetBodyType() const { return BodyType; }

	FString PlayerName;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Tank Stats|Movement");
	float Speed = 550.f;

	UPROPERTY(EditAnywhere, Category = "Tank Stats|Movement");
	float TurnSpeed = 35.f;

	void Move(float Input);
	void Turn(float Input);

	APlayerController* PlayerControllerPointer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn Components", meta = (AllowPrivateAccess = "true"))
	uint8 TurretType;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn Components", meta = (AllowPrivateAccess = "true"))
	uint8 BodyType;

	void Fire();
	void ResetFireCooldown();
	bool bCanFire;

	class UPlayerDisplay* PlayerDisplay;
	void SetPlayerDisplayPointer();

	void UpdateShootStatusIcon();

};
