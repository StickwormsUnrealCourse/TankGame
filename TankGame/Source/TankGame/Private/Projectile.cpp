/*
Base class for fired projectile.

Is provided speed on launch and travel forwards.

*/


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	projectileMovement->bAutoActivate = false;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::LaunchProjectile(float speed)
{
	UE_LOG(LogTemp, Warning, TEXT("Launched at %f"), speed);
	projectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	projectileMovement->Activate();
}

