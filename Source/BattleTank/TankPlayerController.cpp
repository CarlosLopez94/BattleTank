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

bool ATankPlayerController::GetSightRayHitLocation(FVector& outHitLocation) const {
	///Find the crosshair position 
	int32 viewportSizeX;
	int32 viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	FVector2D crosshairScreenLocation = FVector2D(viewportSizeX*crosshairXLocation, viewportSizeY*crosshairYLocation);

	///Deproject crosshairPosition
	FVector lookDirection;
	bool lookSuccess = GetLookDirection(crosshairScreenLocation, lookDirection);
	if (lookSuccess) {
		FHitResult hitResult;
		GetLookVectorHitLocation(lookDirection, hitResult);
		UE_LOG(LogTemp, Warning, TEXT("hitLocation: %s"), *hitResult.Location.ToString());
	}

	//Rail


	return false;
}

/*Get the direction (in world) where is pointing the crosshair. Returns true if the method successed*/
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector CameraWorldLocation; ///not needed
	return  DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}

/**/
bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection, FHitResult& hitResult) const {
	///Get the location of the Camera
	FVector cameraLocation = PlayerCameraManager->GetCameraLocation(); //"GetPlayerViewPoint" can be used too
	
	FVector lineTraceEnd = cameraLocation + lookDirection * lineTraceRange;
	DrawDebugLine(GetWorld(), cameraLocation, lineTraceEnd, FColor::Red, false, 0.f, 0.f, 15.f);

	bool result = GetWorld()->LineTraceSingleByChannel(hitResult,
		cameraLocation,
		lineTraceEnd,
		ECollisionChannel::ECC_Visibility);

	if (!result) {
		hitResult.Location = FVector::ZeroVector;
	}

	return result;
}

