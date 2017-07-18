#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"


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


void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	UE_LOG(LogTemp, Warning, TEXT("Ticking"))
}

void UTankAimingComponent::SetBarrelRef(UStaticMeshComponent * barrelToSet)
{
	barrel = barrelToSet;
}

void UTankAimingComponent::SetTurretRef(UStaticMeshComponent * turretToSet)
{
	turret = turretToSet;
}

void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed)
{
	/*
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at: %s from %s. Velocity: %f"),
		*GetOwner()->GetName(),
		*hitLocation.ToString(),
		*barrel->GetComponentLocation().ToString(),
		launchSpeed);
	*/

	if (!barrel) { return; }

	FVector outLaunchVelocity;
	FVector startPos = barrel->GetSocketLocation(FName("EmissionPos"));

	UGameplayStatics::SuggestProjectileVelocity(this, outLaunchVelocity, startPos, hitLocation, launchSpeed, false, .0f, .0f, ESuggestProjVelocityTraceOption::DoNotTrace);
	
	auto aimDir = outLaunchVelocity.GetSafeNormal(); //Unit Vector
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"),*GetOwner()->GetName(), *aimDir.ToString());

	MoveBarrelTowards(aimDir);

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


