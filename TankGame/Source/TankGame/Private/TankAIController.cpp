/*
Gets the controlled tank and the player tank
Each frame:
Moves towards player
Aims towards player

*/

#include "TankAIController.h"
#include "TankGame.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("%s AITANK Reporting for duty."), *(GetPawn()->GetName()));
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto controlledTank = Cast<ATank>(GetPawn());
	auto playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if (!playerTank) { return; }

	MoveToActor(playerTank, acceptanceRadius);
	controlledTank->AimAt(playerTank->GetActorLocation());
	//controlledTank->Fire();
}
