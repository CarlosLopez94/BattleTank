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
	Aiming,
	Empty
};

//Forward declaration
class UTankTurret;
class UTankBarrel;
class AProjectile;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	EFiringStatus GetFiringState();

	UTankBarrel* GetBarrel();
	void AimAt(FVector aimLocation);
	UFUNCTION(BlueprintCallable)
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus firingState = EFiringStatus::Locked;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float launchSpeed = 8000;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		TSubclassOf<AProjectile> projectileBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float reloadTimeSeconds = 3;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		int32 MAX_AMMO = 3 ;
	UPROPERTY(BlueprintReadOnly, Category = "Firing")
		int32 currentAmmo = 3;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* barrel, UTankTurret* turret);

private:
	FVector lastAimDirection;
	double lastFireTime;
	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;

	void MoveBarrelTowards(FVector aimDirection);
	void MoveTurretTowards(FVector aimDirection);
	bool IsBarrelMoving();
};
