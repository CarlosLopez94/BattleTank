// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineBaseTypes.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming state
UENUM()
enum class EFiringStatus : uint8 {
	Reloading,
	Locked,
	Aiming
};

//Forward declaration
class UTankTurret;
class UTankBarrel;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus firingState = EFiringStatus::Locked;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* barrel, UTankTurret* turret);

public:

	UTankBarrel* GetBarrel();

	void AimAt(FVector aimLocation, float launchSpeed);

	void MoveBarrelTowards(FVector aimDirection);
	void MoveTurretTowards(FVector aimDirection);
private:

	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;

};
