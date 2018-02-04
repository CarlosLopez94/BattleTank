// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialiase(UTankTrack* leftTrack, UTankTrack* rightTrack) {
	this->leftTrack = leftTrack;
	this->rightTrack = rightTrack;
}


void UTankMovementComponent::IntendMoveForwards(float throwValue) {
	if (leftTrack != nullptr && rightTrack != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("%s has %f"), *GetOwner()->GetName(), throwValue);

		leftTrack->SetThrottle(throwValue);
		rightTrack->SetThrottle(throwValue);
	} else {
		UE_LOG(LogTemp, Error, TEXT("TankMovementComponent IntendmoveForwards: At least one of the tracks is null"));
	}
}

void UTankMovementComponent::IntendMoveRight(float throwValue) {
	if (leftTrack != nullptr && rightTrack != nullptr) {
		leftTrack->SetThrottle(-throwValue);
		rightTrack->SetThrottle(throwValue);
	} else {
		UE_LOG(LogTemp, Error, TEXT("TankMovementComponent IntendmoveRight: At least one of the tracks is null"));
	}
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	
	FVector tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector aiForwardIntention = MoveVelocity.GetSafeNormal();

	float dotProduct = FVector::DotProduct(tankForward, aiForwardIntention);

	//UE_LOG(LogTemp, Warning, TEXT("%s has %f"), *GetOwner()->GetName(), dotProduct);
	IntendMoveForwards(1.5*dotProduct);

	FVector crossProduct = FVector::CrossProduct(tankForward, aiForwardIntention);
	IntendMoveRight(2*crossProduct.Z);

}
