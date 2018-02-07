// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.bCanEverTick = true;

}

void UTankTrack::BeginPlay() {
	Super::BeginPlay();
	this->OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}
void UTankTrack::SetThrottle(float throttle) {
	//	UE_LOG(LogTemp, Warning, TEXT("%s is trhotting with value: %f"), *GetName(), throttle);

	FVector forceApplied = GetForwardVector() * throttle * trackMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	float slippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetForwardVector());
	auto correctionAcceleration = slippageSpeed / DeltaTime * GetRightVector();

	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionForce = tankRoot->GetMass() * correctionAcceleration / 2; // divide by two because we have two tracks
	tankRoot->AddForce(correctionAcceleration);

}

void UTankTrack::OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hit) {
	UE_LOG(LogTemp, Warning, TEXT("hit!!!"));
}
