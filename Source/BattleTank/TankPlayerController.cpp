// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "Public/DrawDebugHelpers.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	APawn* controlledTank = GetPawn();
	if (ensure(controlledTank)) {
		tankAimingComponent = controlledTank->FindComponentByClass<UTankAimingComponent>();
		if (ensure(tankAimingComponent)) {
			FoundAimingComponent(tankAimingComponent);
		}
	}
}

//It has to be on this method, if we do this on beginPlay it wont work sometimes and in the contructor is too early
void ATankPlayerController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn != nullptr) {
		auto controlledTank = Cast<ATank>(InPawn);
		if (ensure(controlledTank)) {
			//subscribe
			controlledTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossedTankDeath);
		}
	}
}

void ATankPlayerController::Tick(float deltaTime) {
	Super::Tick(deltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {
	APawn* controlledTank = GetPawn();
	if (ensure(controlledTank)) {
		//Calculate crosshair
		FVector hitLocation;
		bool success = GetSightRayHitLocation(hitLocation);
		if (success) {
			tankAimingComponent->AimAt(hitLocation);
		}
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& vectorHitLocation) const {
	///Find the crosshair position 
	int32 viewportSizeX;
	int32 viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	FVector2D crosshairScreenLocation = FVector2D(viewportSizeX*crosshairXLocation, viewportSizeY*crosshairYLocation);

	///Deproject crosshairPosition
	FVector lookDirection;
	bool lookSuccess = GetLookDirection(crosshairScreenLocation, lookDirection);
	bool hitSuccess = false;
	if (lookSuccess) {
		FHitResult hitResult;
		hitSuccess = GetLookVectorHitLocation(lookDirection, hitResult);
		if (hitSuccess) {
			vectorHitLocation = hitResult.Location;
		}
	}

	return hitSuccess;
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

bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection, FHitResult& hitResult) const {
	///Get the location of the Camera
	FVector cameraLocation = PlayerCameraManager->GetCameraLocation(); //"GetPlayerViewPoint" can be used too

	FVector lineTraceEnd = cameraLocation + lookDirection * lineTraceRange;
	//DrawDebugLine(GetWorld(), cameraLocation, lineTraceEnd, FColor::Red, false, 0.f, 0.f, 15.f);

	bool result = GetWorld()->LineTraceSingleByChannel(hitResult,
		cameraLocation,
		lineTraceEnd,
		ECollisionChannel::ECC_Camera);

	if (!result) {
		hitResult.Location = FVector::ZeroVector;
	}

	return result;
}

void ATankPlayerController::OnPossedTankDeath() {
	//UE_LOG(LogTemp, Warning, TEXT("tank has die. Received on player controlled"));
	StartSpectatingOnly();
}

