// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay(){
	Super::BeginPlay();
	ATank* controlledTank = GetControlledTank();
	if (controlledTank!=nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController controls %s"),*controlledTank->GetName());
	} else {
		UE_LOG(LogTemp, Error, TEXT("TankPlayerController IS NOT controlling any tank"));
	}
}

/*
Returns the controlled tank or nullptr if there isnt any
*/
ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}



