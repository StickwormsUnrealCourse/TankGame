/*
Sets refs to: tank, aimingComp
Uses FoundAimingComponent to set a reference in blueprint
Tick uses AimTowardsCrosshair to get the camera hit location to drive the AimAt on tank
GetSightRayHitLocation finds what the screen crosshair is pointing at

*/

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankGame.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (!ensure(GetPawn())) { return; }	//might not be possesing.
	aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (aimingComponent)
	{
		FoundAimingComponent(aimingComponent);
	}

	//TODO THis looks dodgy in the blueprint, relies on aiming component being found and generating the UI widgit first.
	auto tankRef = Cast<ATank>(GetPawn());
	if (tankRef)
	{
		SetTankRef(tankRef);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
}

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!ensure(aimingComponent)) { return; }

	FVector hitLocation = FVector(0.0f);
	if (GetSightRayHitLocation(hitLocation))	//Side Effect: RayTrace
	{
		//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *hitLocation.ToString());
		aimingComponent->AimAt(hitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& hitLocation) const
{
	//Find crosshair in pixel coords
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	FVector2D screenLocation = FVector2D(viewportSizeX * crosshairXLoc, viewportSizeY * crosshairYLoc);

	//Deproject though crosshair on screen
	FVector worldDirection, camWorldLoc;
	DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, camWorldLoc, worldDirection);

	FHitResult hit;
	GetWorld()->LineTraceSingleByChannel(
		hit,
		camWorldLoc,
		camWorldLoc + worldDirection * 999999999.0f,	//Max Range
		ECollisionChannel::ECC_Visibility
		);
	hitLocation = hit.Location;

	//UE_LOG(LogTemp, Warning, TEXT("Target: %i"), hit.IsValidBlockingHit());

	if (hit.IsValidBlockingHit()) {return true;}
	return false;
}

