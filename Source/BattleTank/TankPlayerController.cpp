// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "Public/DrawDebugHelpers.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	ATank* controlledTank = GetControlledTank();
	if (controlledTank != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController controls %s"), *controlledTank->GetName());
	} else {
		UE_LOG(LogTemp, Error, TEXT("TankPlayerController IS NOT controlling any tank"));
	}
}

void ATankPlayerController::Tick(float deltaTime) {
	Super::Tick(deltaTime);
	AimTowardsCrosshair();
}

/*
Returns the controlled tank or nullptr if there isnt any
*/
ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrosshair() {
	//Calculate crosshair
	FVector hitLocation;
	GetSightRayHitLocation(hitLocation);

	//calculate crosshair position in world

	//calculate rotation

	//rotate barrel
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& outHitLocation) const{
	///Find the crosshair position
	int32 viewportSizeX;
	int32 viewportSizeY;
	GetViewportSize(viewportSizeX,viewportSizeY);
	auto crosshairScreenLocation = FVector2D(viewportSizeX*crosshairXLocation,viewportSizeY*crosshairYLocation);
	
	/*///Deproject crosshairPosition
	FVector2D crosshairInWorld = FVector2D();
	DeprojectScreenPositionToWorld(crosshairScreenLocation.X, crosshairYLocation, crosshairInWorld.X, crosshairInWorld.Y);*/
	return false;
}


