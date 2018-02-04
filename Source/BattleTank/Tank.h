// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankMovementComponent;
class UTankAimingComponent;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SetBarrelReference(UTankBarrel* barrelMesh);

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SetTurretReference(UTankTurret* turretMesh);


	void AimAt(FVector aimLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

	//Variables
	
	UTankBarrel* barrel = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		TSubclassOf<AProjectile> projectileBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float launchSpeed = 4000;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float reloadTimeSeconds = 2;

private:
	double lastFireTime;

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent * tankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
		UTankMovementComponent* tankMovementComponent = nullptr;
};
