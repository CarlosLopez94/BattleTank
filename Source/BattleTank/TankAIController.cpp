// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	tankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float deltaTime) {
	Super::Tick(deltaTime);
	APawn* controlledTank = GetPawn();
	APawn* playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (ensure(controlledTank && playerTank)) {
		///Move towards the player
		MoveToActor(playerTank, acceptanceRadius);

		///Get aim location
		FVector aimLocation = playerTank->GetActorLocation();

		//UE_LOG(LogTemp, Warning, TEXT("TankAIController %s"), *controlledTank->GetName());
		tankAimingComponent->AimAt(aimLocation);
		if (tankAimingComponent->GetFiringState() == EFiringStatus::Locked) {
			tankAimingComponent->Fire();
		}
	}
}