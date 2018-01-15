// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


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

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* barrelMesh) {
	barrel = barrelMesh;
}


void UTankAimingComponent::AimAt(FVector locationToAim, float launchSpeed) const {
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
			auto aimDirection = outLaunchVelocity.GetSafeNormal();
			UE_LOG(LogTemp, Warning, TEXT("%s aiming at [%s]"),*GetOwner()->GetName(),*aimDirection.ToString());
		}
	}
}
