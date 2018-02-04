// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineBaseTypes.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming state
UENUM()
enum class EFiringStatus : uint8 {
	Locked,
	Aiming,
	Reloading
};

//Forward declaration
class UTankTurret;
class UTankBarrel; 

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus firingState = EFiringStatus::Reloading;
public:	

	void SetBarrelReference(UTankBarrel* barrelMesh);
	void SetTurretReference(UTankTurret* turretMesh);
	UTankBarrel* GetBarrel();

	void AimAt(FVector aimLocation, float launchSpeed);

	void MoveBarrelTowards(FVector aimDirection);
	void MoveTurretTowards(FVector aimDirection);
private:

	UTankAimingComponent * tankAimingComponent = nullptr;
	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;
	
};
