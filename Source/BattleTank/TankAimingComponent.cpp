// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TankBarrel.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrelMesh) {
	barrel = barrelMesh;
}


void UTankAimingComponent::AimAt(FVector locationToAim, float launchSpeed) {
	if (barrel != nullptr) {

		FVector outLaunchVelocity;
		FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));

		///Calculate the outlaunchVelocity
		bool success = UGameplayStatics::SuggestProjectileVelocity(
			this,
			outLaunchVelocity,
			startLocation,
			locationToAim,
			launchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace);

		if (success) {
			FVector aimDirection = outLaunchVelocity.GetSafeNormal();
			UE_LOG(LogTemp, Warning, TEXT("[%f] aim solution found"), GetWorld()->GetTimeSeconds());
			MoveBarrelTowards(aimDirection);
		}else{
			UE_LOG(LogTemp, Warning, TEXT("[%f] NO aim solution found"), GetWorld()->GetTimeSeconds());
		}
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection) {
	//Calculate rotation and location (where is pointing it?)
	auto barrelRotator = barrel->GetForwardVector().Rotation();
	auto aimRotator = aimDirection.Rotation();
	auto deltaRotator = aimRotator - barrelRotator;

	barrel->Elevate(deltaRotator.Pitch);
}
