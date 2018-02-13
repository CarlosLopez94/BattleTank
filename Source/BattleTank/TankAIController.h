// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly)
		UTankAimingComponent* tankAimingComponent = nullptr;
	


private:
	float acceptanceRadius = 8000;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
		void OnPossedTankDeath();
};
