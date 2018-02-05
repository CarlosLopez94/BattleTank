// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController {
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
		UTankAimingComponent* tankAimingComponent = nullptr;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* aimCompRef);
private:
	UPROPERTY(EditDefaultsOnly, Category = "Screen Interface")
		float crosshairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Screen Interface")
		float crosshairYLocation = 0.5;

	float lineTraceRange = 1000000.f;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& hitLocation) const;
	bool GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const;
	bool GetLookVectorHitLocation(FVector lookDirection, FHitResult& hitResult) const;

};
