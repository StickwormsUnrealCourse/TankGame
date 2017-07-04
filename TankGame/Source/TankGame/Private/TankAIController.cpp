// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankGame.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto tank = GetControlledTank();
	if (tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI tank found: %s"), *(tank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI tank not found"));
	}
}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}