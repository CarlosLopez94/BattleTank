// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankMovementComponent.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Engine/World.h"
#include "Projectile.h"


// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}
void ATank::BeginPlay() {
	Super::BeginPlay();
	//tankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

void ATank::Fire() {
	//double firingTime = FPlatformTime::Seconds();
	//bool isReloaded = (firingTime - lastFireTime) > reloadTimeSeconds;
	//UTankBarrel* barrel = nullptr;
	//
	//if (GetWorld()->GetFirstPlayerController() !=nullptr) {
	//	barrel = tankAimingComponent->GetBarrel();
	//}

	//if (ensure(barrel)) {
	//	if (isReloaded) {
	//		FVector projectileLocation = barrel->GetSocketLocation(FName("Projectile"));
	//		FRotator projectileRotation = barrel->GetSocketRotation(FName("Projectile"));
	//		auto projectile = GetWorld()->SpawnActor<AProjectile>(projectileBlueprint, projectileLocation, projectileRotation);
	//		if (ensure(projectile)) {
	//			projectile->LaunchProjectile(4000);
	//		}
	//		lastFireTime = firingTime;
	//	}
	//}
}

//void ATank::AimAt(FVector aimLocation) {
//	if (ensure(tankAimingComponent)) {
//		tankAimingComponent->AimAt(aimLocation);
//	}
//}

