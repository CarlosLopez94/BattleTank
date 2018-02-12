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
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	UFUNCTION(BluEprintPure, Category = "Health")
	float GetHealthPercentage() const;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 MAX_HEALTH = 100;
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 currentHealth = MAX_HEALTH;
};
