// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float deltaTime) {
	Super::Tick(deltaTime);
	ATank* controlledTank = Cast<ATank>(GetPawn());
	ATank* playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (controlledTank != nullptr && playerTank != nullptr) {
		///Get aim location
		FVector aimLocation = playerTank->GetActorLocation();

		///delegate to the tank
		//UE_LOG(LogTemp, Warning, TEXT("TankAIController %s"), *controlledTank->GetName());
		controlledTank->AimAt(aimLocation);
		controlledTank->Fire();
	}
}