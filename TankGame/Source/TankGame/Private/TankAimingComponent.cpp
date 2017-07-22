/*
Sets refs to: barrel, turret
AimAt function: takes a desired location and launch speed to calculate an aiming direction,
then uses MoveBarrelTowards to position the barrel for firing.
*/

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"


UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::Initialise(UStaticMeshComponent* barrelToSet, UStaticMeshComponent* turretToSet)
{
	barrel = barrelToSet;
	turret = turretToSet;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	//UE_LOG(LogTemp, Warning, TEXT("Ticking"))

	//Super::TickComponent();

	if (!IsReloaded())
	{
		firingState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		firingState = EFiringState::Aiming;
	}
	else
	{
		firingState = EFiringState::Locked;
	}
}

bool UTankAimingComponent::IsReloaded()
{
	if((FPlatformTime::Seconds() - lastFiredTimeStamp) > reloadTime)
	{
		return true;
	}
	return false;
}

void UTankAimingComponent::AimAt(FVector hitLocation)
{
	/*
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at: %s from %s. Velocity: %f"),
		*GetOwner()->GetName(),
		*hitLocation.ToString(),
		*barrel->GetComponentLocation().ToString(),
		launchSpeed);
	*/

	if (!ensure(barrel)) { return; }

	FVector outLaunchVelocity;
	FVector startPos = barrel->GetSocketLocation(FName("EmissionPos"));

	UGameplayStatics::SuggestProjectileVelocity(this, outLaunchVelocity, startPos, hitLocation, launchSpeed, false, .0f, .0f, ESuggestProjVelocityTraceOption::DoNotTrace);
	
	aimDir = outLaunchVelocity.GetSafeNormal(); //Unit Vector
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"),*GetOwner()->GetName(), *aimDir.ToString());

	MoveBarrelTowards(aimDir);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	auto barrelForward = barrel->GetForwardVector();
	return !(barrelForward.Equals(aimDir, 0.01f));
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	//Find difference between current barrel rotation and aim direction
	auto barrelRotator = barrel->GetForwardVector().Rotation();
	auto aimAsRotator = aimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;

	RotateTurret(deltaRotator.Yaw);
	ElevateBarrel(deltaRotator.Pitch);
}


void UTankAimingComponent::ElevateBarrel(float relativeSpeed)
{
	auto elevationChange = relativeSpeed * elevationSpeed * GetWorld()->DeltaTimeSeconds;
	auto elevation = barrel->RelativeRotation.Pitch + elevationChange;
	elevation = FMath::Clamp<float>(elevation, minElevation, maxElevation);
	
	barrel->SetRelativeRotation(FRotator(elevation, .0f, .0f));
}

void UTankAimingComponent::RotateTurret(float relativeSpeed)
{
	auto rotationChange = relativeSpeed * turretRotationSpeed * GetWorld()->DeltaTimeSeconds;
	auto rotation = turret->RelativeRotation.Yaw + rotationChange;
	//rotation = FMath::Clamp<float>(rotation, minTurretRotation, maxTurretRotation);

	turret->SetRelativeRotation(FRotator(.0f, rotation, .0f));
}


void UTankAimingComponent::Fire()
{
	if (!ensure(barrel)) { return; }

	auto emissionPos = barrel->GetSocketLocation("EmissionPos");
	auto emissionRot = barrel->GetSocketRotation("EmissionPos");

	if (IsReloaded())
	{
		auto projectile = GetWorld()->SpawnActor<AProjectile>(projectile_BP, emissionPos, emissionRot);
		projectile->LaunchProjectile(launchSpeed);
		lastFiredTimeStamp = FPlatformTime::Seconds();
	}
}