// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	ATank* controlledTank = GetControlledTank();
	if (controlledTank != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController controls %s"), *controlledTank->GetName());
	} else {
		UE_LOG(LogTemp, Error, TEXT("TankAIController IS NOT controlling any tank"));
	}

	ATank* playerTank = GetPlayerTank();
	if (playerTank != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController reach player tank: %s"), *playerTank->GetName());
	} else {
		UE_LOG(LogTemp, Error, TEXT("TankAIController DOESN'T reach player tank"));
	}
}

void ATankAIController::Tick(float deltaTime) {
	Super::Tick(deltaTime);
	AimTowardsCrosshair();
}

/*Returns the controlled tank or nullptr if there isnt any*/
ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

/*
Returns the tank controlled by the player
*/
ATank* ATankAIController::GetPlayerTank() const {
	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	if (playerController != nullptr && playerController->GetPawn() != nullptr) {
		return Cast<ATank>(playerController->GetPawn());
	} else {
		return nullptr;
	}
}

/*Moves the barrel to the position where the crosshair intersecs*/
void ATankAIController::AimTowardsCrosshair() {
	ATank* controlledTank = GetPlayerTank();
	if (controlledTank!=nullptr) {
		///Get aim location
		FVector aimLocation = controlledTank->GetActorLocation();

		///delegate to the tank
		UE_LOG(LogTemp, Warning, TEXT("TankAIController %s"), *controlledTank->GetName());
		controlledTank->AimAt(aimLocation);
	}
}