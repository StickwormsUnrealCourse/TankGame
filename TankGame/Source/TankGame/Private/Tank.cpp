// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "../Public/Tank.h"


void ATank::SetBarrelRef(UStaticMeshComponent * barrelToSet)
{
	TankAimingComponent->SetBarrelRef(barrelToSet);
}

void ATank::SetTurretRef(UStaticMeshComponent * turretToSet)
{
	TankAimingComponent->SetTurretRef(turretToSet);
}

ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

void ATank::AimAt(FVector hitLocation)
{
	TankAimingComponent->AimAt(hitLocation, launchSpeed);
}

