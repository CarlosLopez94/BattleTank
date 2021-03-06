// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay() {
	Super::BeginPlay();
	lastFireTime = FPlatformTime::Seconds();
	currentAmmo = MAX_AMMO;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	double currentTime = FPlatformTime::Seconds();
	if (currentAmmo<=0) {
		firingState = EFiringStatus::Empty;
	} else if ((currentTime - lastFireTime) < reloadTimeSeconds) {
		firingState = EFiringStatus::Reloading;
	} else if (IsBarrelMoving()) {
		firingState = EFiringStatus::Aiming;
	} else {
		firingState = EFiringStatus::Locked;
	}
	//UE_LOG(LogTemp, Warning, TEXT("[%f] .......... %i"), GetWorld()->GetTimeSeconds(), currentAmmo);
}

EFiringStatus UTankAimingComponent::GetFiringState() {
	return firingState;
}

void UTankAimingComponent::Initialise(UTankBarrel* barrelMesh, UTankTurret* turretMesh) {
	barrel = barrelMesh;
	turret = turretMesh;
}

UTankBarrel* UTankAimingComponent::GetBarrel() {
	return barrel;
}


void UTankAimingComponent::AimAt(FVector locationToAim) {
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
			lastAimDirection = outLaunchVelocity.GetSafeNormal();
			MoveTurretTowards(lastAimDirection);
			MoveBarrelTowards(lastAimDirection);
		} else {
			UE_LOG(LogTemp, Warning, TEXT("[%f] NO aim solution found"), GetWorld()->GetTimeSeconds());
		}
	}
}

void UTankAimingComponent::Fire() {
	if (ensure(barrel)) {
		if (firingState == EFiringStatus::Locked || firingState == EFiringStatus::Aiming) {
			FVector projectileLocation = barrel->GetSocketLocation(FName("Projectile"));
			FRotator projectileRotation = barrel->GetSocketRotation(FName("Projectile"));
			auto projectile = GetWorld()->SpawnActor<AProjectile>(projectileBlueprint, projectileLocation, projectileRotation);
			if (ensure(projectile)) {
				projectile->LaunchProjectile(launchSpeed);
			}
			lastFireTime = FPlatformTime::Seconds();
			
			//decrease ammo and check
			currentAmmo--;
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

	float desireDegree;
	if (FMath::Abs(deltaRotator.Yaw)<180) {
		desireDegree = deltaRotator.Yaw;
	} else {
		desireDegree = -deltaRotator.Yaw;
	}
	turret->Rotate(desireDegree);
}

bool UTankAimingComponent::IsBarrelMoving() {
	bool isMoving = false;
	if (ensure(barrel)) {
		isMoving = !barrel->GetForwardVector().GetSafeNormal().Equals(lastAimDirection, 0.01f);
	}
	return isMoving;
}

