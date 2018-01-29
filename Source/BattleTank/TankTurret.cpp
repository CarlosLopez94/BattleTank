// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"


void UTankTurret::Rotate(float turnSpeed) {
	float clampedRelativeSpeed = FMath::Clamp(turnSpeed, -1.f, 1.f);
	float turnChange = turnSpeed * maxDegressPerSecond* GetWorld()->GetDeltaSeconds();
	float newTurnDegree = RelativeRotation.Yaw + turnChange;
	//UE_LOG(LogTemp, Warning, TEXT("[%f] turret degree %f"), GetWorld()->GetTimeSeconds(), newTurnDegree);

	//set the new rotation
	SetRelativeRotation(FRotator(0, newTurnDegree, 0));
}

