// Fill out your copyright notice in the Description page of Project Settings.



#include "TankAimingComponent.h"
#include "../Public/TankAimingComponent.h"
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


void UTankAimingComponent::SetBarrelRef(UStaticMeshComponent * barrelToSet)
{
	barrel = barrelToSet;
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"),*GetOwner()->GetName(), *aimDir.ToString());

}

