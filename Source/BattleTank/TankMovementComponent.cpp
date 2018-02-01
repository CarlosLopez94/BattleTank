// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialiase(UTankTrack* leftTrack, UTankTrack* rightTrack) {
	if (leftTrack!=nullptr && rightTrack!=nullptr) {
		this->leftTrack = leftTrack;
		this->rightTrack = rightTrack;
	} else {
		UE_LOG(LogTemp, Error, TEXT("TankMovementComponent: At least one of the tracks is null"));
	}
}


void UTankMovementComponent::IntendMoveForwards(float throwValue) {
	UE_LOG(LogTemp, Warning, TEXT("intened move forwards : %f"), throwValue);

	leftTrack->SetThrottle(throwValue);
	rightTrack->SetThrottle(throwValue);
}

