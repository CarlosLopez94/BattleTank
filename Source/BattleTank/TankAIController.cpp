// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	tankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

//It has to be on this method, if we do this on beginPlay it wont work sometimes and in the contructor is too early
void ATankAIController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn!=nullptr) {
		auto controlledTank = Cast<ATank>(InPawn);
		if (ensure(controlledTank)) {
			//subscribe
			controlledTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
		}
	}
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

void ATankAIController::OnPossedTankDeath() {
	//UE_LOG(LogTemp, Warning, TEXT("tank has die. EEEEEEEEEEEEEEEEEEEEEEEEEE AI"));
	GetPawn()->DetachFromControllerPendingDestroy();
}