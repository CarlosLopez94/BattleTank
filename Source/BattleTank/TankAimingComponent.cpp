// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* barrelMesh, UTankTurret* turretMesh) {
	barrel = barrelMesh;
	turret = turretMesh;
}

UTankBarrel* UTankAimingComponent::GetBarrel() {
	return barrel;
}


void UTankAimingComponent::AimAt(FVector locationToAim, float launchSpeed) {
	if (ensure(barrel && turret)) {

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
			//UE_LOG(LogTemp, Warning, TEXT("[%f] aim solution found"), GetWorld()->GetTimeSeconds());
			MoveTurretTowards(aimDirection);
			MoveBarrelTowards(aimDirection);
		} else {
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

void UTankAimingComponent::MoveTurretTowards(FVector aimDirection) {
	//Calculate rotation and location (where is pointing it?)
	auto turretRotator = turret->GetForwardVector().Rotation();
	auto aimRotator = aimDirection.Rotation();
	auto deltaRotator = aimRotator - turretRotator;

	turret->Rotate(deltaRotator.Yaw);
}

