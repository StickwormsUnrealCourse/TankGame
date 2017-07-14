// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankGame.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("%s AITANK Reporting for duty."), *(GetPawn()->GetName()));
	
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto controlledTank = Cast<ATank>(GetPawn());
	auto playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if (!playerTank) { return; }

	controlledTank->AimAt(playerTank->GetActorLocation());
	controlledTank->Fire();
	
}
