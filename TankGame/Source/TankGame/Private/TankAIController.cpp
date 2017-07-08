// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankGame.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto tank = GetControlledTank();
	if (!tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI tank not found"));
	}
	
	auto playerTank = GetPlayerTank();
	if (playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI tank found Player tank: %s"), *(playerTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI tank could not find player"));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!playerPawn) {return nullptr;}
	return Cast<ATank>(playerPawn);
}