// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "TankAIController.generated.h"


UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly)
		UTankAimingComponent* tankAimingComponent = nullptr;

private:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

	float acceptanceRadius = 8000;

};
