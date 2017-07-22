/*
Tank
Binds functionality to input
Sets refs to: body, barrel, turret
Passes the hitlocation of the viewport to the AimAt component
Spawns and fires the projectile checking if its reloaded or not from the barrel socket
Sets left and right throttle (using sockets on the tank body)

*/

#include "Tank.h"
#include "TankMovementComponent.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
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