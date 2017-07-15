#include "Tank.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
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

void ATank::SetBodyRef(UStaticMeshComponent * bodyToSet)
{
	body = bodyToSet;
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
	
	bool isReloaded = (FPlatformTime::Seconds() - lastFiredTimeStamp) > reloadTime;

	if (isReloaded)
	{
		auto projectile = GetWorld()->SpawnActor<AProjectile>(projectile_BP, emissionPos, emissionRot);
		projectile->LaunchProjectile(launchSpeed);
		lastFiredTimeStamp = FPlatformTime::Seconds();
	}
}

void ATank::SetLeftThrottle(float throttle)
{
	//UE_LOG(LogTemp, Warning, TEXT("Left Throttle: %f"), throttle);
	
	if (!body) { return; }

	auto forceApplied = body->GetForwardVector() * throttle * maxThrottleForce;
	auto forceLocation = body->GetSocketLocation("LTrack");
	//auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	body->AddForceAtLocation(forceApplied, forceLocation);
	
}

void ATank::SetRightThrottle(float throttle)
{
	//UE_LOG(LogTemp, Warning, TEXT("Right Throttle: %f"), throttle);

	if (!body) { return; }

	auto forceApplied = body->GetForwardVector() * throttle * maxThrottleForce;
	auto forceLocation = body->GetSocketLocation("RTrack");
	//auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	body->AddForceAtLocation(forceApplied, forceLocation);
}
