// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float relativeSpeed) {
	float clampedRelativeSpeed = FMath::Clamp(relativeSpeed,-1.f,1.f);
	float elevationChange = clampedRelativeSpeed * maxDegressPerSecond* GetWorld()->GetDeltaSeconds();
	float rawNewElevation = RelativeRotation.Pitch + elevationChange;
	rawNewElevation = FMath::Clamp(rawNewElevation,minElevationDegrees,maxElevationDegrees);

	//set the new rotation
	SetRelativeRotation(FRotator(rawNewElevation,0,0));
}



