// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}
void ATank::BeginPlay() {
	Super::BeginPlay();
	currentHealth = MAX_HEALTH;
}

float ATank::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	int32 damageToApply = FMath::Clamp<int32>(FPlatformMath::RoundToInt(Damage),0, currentHealth);
	currentHealth = currentHealth - damageToApply;

	//Camera shake

	//Check if tank stills alive
	if (currentHealth <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("tank %s has died :("),*GetName());
		OnDeath.Broadcast();
	}
	return damageToApply;
}

float ATank::GetHealthPercentage() const{
	return (float)currentHealth / (float)MAX_HEALTH;
}
