/*
Gets the controlled tank and the player tank
Each frame:
Moves towards player
Aims towards player

*/

#include "TankAIController.h"
#include "TankGame.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("%s AITANK Reporting for duty."), *(GetPawn()->GetName()));

	aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

//Subscribe to delegate on possesion as BeginPlay may be too early
void ATankAIController::SetPawn(APawn* inPawn)
{
	Super::SetPawn(inPawn);
	if (inPawn)
	{
		auto possessedTank = Cast<ATank>(inPawn);
		if (!ensure(possessedTank)) { return; }

		//Subscribe and like!
		possessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto player = GetWorld()->GetFirstPlayerController()->GetPawn();	
	if (!ensure(player)) { return; }

	MoveToActor(player, acceptanceRadius);

	aimingComponent->AimAt(player->GetActorLocation());
	
	if (aimingComponent->GetFiringState() == EFiringState::Locked)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AI %s Is Locked."), *(GetPawn()->GetName()));
		aimingComponent->Fire();
	}
}

void ATankAIController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("%s has died."), *(GetName()));
	GetPawn()->DetachFromControllerPendingDestroy();
}