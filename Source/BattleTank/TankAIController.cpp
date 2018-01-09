// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	ATank* controlledTank = GetControlledTank();
	if (controlledTank != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController controls %s"), *controlledTank->GetName());
	} else {
		UE_LOG(LogTemp, Error, TEXT("TankAIController IS NOT controlling any tank"));
	}
}

/*
Returns the controlled tank or nullptr if there isnt any
*/
ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}



