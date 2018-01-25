// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float degressPerSecond);
	
private:
	UPROPERTY(EditAnywhere, Category = "Setup")
		float maxDegressPerSecond=20;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float maxElevationDegrees=40;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float minElevationDegrees = 0;

	
};
