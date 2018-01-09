// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"

/**
 *
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController {
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Screen Interface")
		float crosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Screen Interface")
		float crosshairYLocation = 0.33333333f;

private:
	ATank * GetControlledTank() const;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& hitLocation) const;
	bool GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const;
};
