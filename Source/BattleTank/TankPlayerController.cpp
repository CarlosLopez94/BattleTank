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
	/*FVector playerViewPointLocation;
	FRotator playerViewPointRotation;
	GetPlayerViewPoint(playerViewPointLocation,
		playerViewPointRotation);

	///Draw a red trace in the world
	FVector lineTraceEnd = playerViewPointLocation + playerViewPointRotation.Vector() * 50000; //replace by tank shoot range
	DrawDebugLine(GetWorld(), playerViewPointLocation, lineTraceEnd, FColor::Red, false, 0.f, 0.f, 25.f);
	///Setup query parameters
	FCollisionQueryParams traceParameters = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());

	///Line-trace: Ray-cast out the reach distance
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(
		hit,
		playerViewPointLocation,
		lineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
		traceParameters);

	///See what we hit
	if (hit.Actor != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("can grabber %s, pos: %s"), *hit.Actor->GetName(), *hit.Actor->GetActorLocation().ToString());
		return true;
	} else {
		UE_LOG(LogTemp, Warning, TEXT("No actor"), );
		return false;
	}
	*/
	return false;
}


