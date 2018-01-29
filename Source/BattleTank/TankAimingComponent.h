// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineBaseTypes.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel; //Forward declaration

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void SetBarrelReference(UTankBarrel* barrelMesh);

	void AimAt(FVector aimLocation, float launchSpeed);

	void MoveBarrelTowards(FVector aimDirection);

private:

	UTankAimingComponent * tankAimingComponent = nullptr;
	UTankBarrel* barrel = nullptr;
};
