// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetBarrelReference(UTankBarrel* barrelMesh);

	void AimAt(FVector aimLocation);


private:
	UPROPERTY(EditAnywhere, Category = "Firing")
		float launchSpeed = 10000; //find sensible initial velocity
	UTankAimingComponent* tankAimingComponent = nullptr;
	UTankBarrel* barrel = nullptr;
};
