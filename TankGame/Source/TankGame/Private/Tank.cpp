#include "Tank.h"
#include "Projectile.h"


ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::SetBarrelRef(UStaticMeshComponent * barrelToSet)
{
	TankAimingComponent->SetBarrelRef(barrelToSet);
	barrel = barrelToSet;
}


void ATank::SetTurretRef(UStaticMeshComponent * turretToSet)
{
	TankAimingComponent->SetTurretRef(turretToSet);
}

void ATank::AimAt(FVector hitLocation)
{
	TankAimingComponent->AimAt(hitLocation, launchSpeed);
}

void ATank::Fire()
{
	if (!barrel) { return; }
	
	auto emissionPos = barrel->GetSocketLocation("EmissionPos");
	auto emissionRot = barrel->GetSocketRotation("EmissionPos");
	auto projectile = GetWorld()->SpawnActor<AProjectile>(projectile_BP, emissionPos, emissionRot);
	projectile->LaunchProjectile(launchSpeed);

}