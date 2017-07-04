// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankGame.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Begin Play in Tank Controller!"));

	auto tank = GetControlledTank();
	if (tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("tank found: %s"), *(tank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("tank not found"));
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


