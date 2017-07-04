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

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


