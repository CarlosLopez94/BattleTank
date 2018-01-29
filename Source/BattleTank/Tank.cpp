// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Engine/World.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	///No need to protect points as added at constructor

	///Set aimingComponent reference
	tankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));



}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::SetBarrelReference(UTankBarrel* barrelComponent) {
	if (tankAimingComponent) {
		tankAimingComponent->SetBarrelReference(barrelComponent);
		barrel = tankAimingComponent->GetBarrel();
	}
}


void ATank::SetTurretReference(UTankTurret* turretMesh) {
	if (tankAimingComponent!=nullptr) {
		tankAimingComponent->SetTurretReference(turretMesh);
	}
}

void ATank::Fire() {
	UE_LOG(LogTemp, Warning, TEXT("Firing!!!"));
	if (barrel!=nullptr) {
		FVector projectileLocation = barrel->GetSocketLocation(FName("Projectile"));
		FRotator projectileRotation = barrel->GetSocketRotation(FName("Projectile"));
		auto projectile = GetWorld()->SpawnActor<AProjectile>(projectileBlueprint,projectileLocation,projectileRotation);
	
		projectile->LaunchProjectile(launchSpeed);
	} else {
		//log
	}
}

void ATank::AimAt(FVector aimLocation) {
	if (tankAimingComponent != nullptr) {
		tankAimingComponent->AimAt(aimLocation, launchSpeed);
	}
}

