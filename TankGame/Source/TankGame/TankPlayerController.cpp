// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankGame.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto tank = GetControlledTank();
	if (tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tank found: %s"), *(tank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tank not found"));
	}
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
}

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetControlledTank()) { return; }

	FVector hitLocation = FVector(0.0f);
	if (GetSightRayHitLocation(hitLocation))	//Side Effect: RayTrace
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *hitLocation.ToString());
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

	if (hit.IsValidBlockingHit()) {return true;}
	return false;
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


