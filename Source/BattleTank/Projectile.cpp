// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Engine/World.h"
#include "Public/TimerManager.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh Component"));
	SetRootComponent(collisionMesh);
	collisionMesh->SetNotifyRigidBodyCollision(true);
	collisionMesh->SetVisibility(false);

	launchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Particle System Component - launch blast"));
	launchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	impactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Particle System Component - impact blast"));
	impactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	impactBlast->bAutoActivate = false;

	projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));
	projectileMovementComponent->bAutoActivate = false;

	exposionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	exposionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	collisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hit) {
	//logic
	impactBlast->Activate();
	launchBlast->Deactivate();
	exposionForce->FireImpulse();
	UE_LOG(LogTemp, Warning, TEXT("activating!"));

	//Destroy mesh component
	SetRootComponent(exposionForce);
	collisionMesh->DestroyComponent();

	FTimerHandle fTimerHandle; 
	float time = 0; 
	GetWorld()->GetTimerManager().SetTimer(fTimerHandle, this, &AProjectile::DestroyProjectile, destroyDelay, false);
	
	//(fTimerHandle, time, false);
	
}

void AProjectile::LaunchProjectile(float speed) {
	projectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector*speed);
	projectileMovementComponent->Activate();
}

void AProjectile::DestroyProjectile() {
	UE_LOG(LogTemp, Warning, TEXT("%s destroy!"), *GetName());
	Destroy();
}