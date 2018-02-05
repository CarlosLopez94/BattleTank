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
	virtual void BeginPlay() override;

	//void AimAt(FVector aimLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

	//Variables
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		TSubclassOf<AProjectile> projectileBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float reloadTimeSeconds = 2;

private:
	double lastFireTime;

protected:
	UPROPERTY(BlueprintReadOnly)
		UTankMovementComponent* tankMovementComponent = nullptr;
};
