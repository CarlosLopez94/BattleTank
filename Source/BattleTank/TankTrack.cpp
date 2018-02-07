// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.bCanEverTick = true;

}

void UTankTrack::BeginPlay() {
	Super::BeginPlay();
	this->OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hit) {
	//UE_LOG(LogTemp, Warning, TEXT("hit!!!"));
	//update tank position
	DriveTank();
	//correct tank movement
	ApplySidewaysForce();
	
	currentThrottle = 0;
}

void UTankTrack::SetThrottle(float throttle) {
	currentThrottle = FMath::Clamp<float>(currentThrottle + throttle, -1.f, 1.f);
	UE_LOG(LogTemp, Warning, TEXT("currentthrotlñe: %f"), currentThrottle);

}

void UTankTrack::DriveTank() {
	FVector forceApplied = GetForwardVector() * currentThrottle * trackMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}


void UTankTrack::ApplySidewaysForce() {
	float slippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetForwardVector());
	auto correctionAcceleration = slippageSpeed / GetWorld()->GetDeltaSeconds() * GetRightVector();

	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionForce = tankRoot->GetMass() * correctionAcceleration / 2; // divide by two because we have two tracks
	tankRoot->AddForce(correctionAcceleration);
	UE_LOG(LogTemp, Warning, TEXT("[%f] force applied"), GetWorld()->GetTimeSeconds());
}