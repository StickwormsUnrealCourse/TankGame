#include "TankMovementComponent.h"
#include "Tank.h"

void UTankMovementComponent::Initialise(UStaticMeshComponent* bodyToSet)
{
	body = bodyToSet;
	controlledTank = Cast<ATank>(GetOwner());	
}


void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//No Super as we're replacing the functionality

	auto tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto forwardVector = FVector::DotProduct(tankForward, AIForwardIntention);
	IntendMoveForward(forwardVector);

	auto turningVector = FVector::CrossProduct(tankForward, AIForwardIntention);
	IntendTurnRight(turningVector.Z);

	//UE_LOG(LogTemp, Warning, TEXT("%s, Vectoring: %s"), *(controlledTank->GetName()), *MoveVelocity.GetSafeNormal().ToString());
}


void UTankMovementComponent::IntendMoveForward(float amount)
{
	//UE_LOG(LogTemp, Warning, TEXT("IntendMoveForward: %f"), amount);

	if (!controlledTank) { return; }
	
	controlledTank->SetLeftThrottle(amount);
	controlledTank->SetRightThrottle(amount);
}

void UTankMovementComponent::IntendTurnRight(float amount)
{
	//UE_LOG(LogTemp, Warning, TEXT("IntendMoveRight: %f"), amount);

	if (!controlledTank) { return; }

	controlledTank->SetLeftThrottle(amount);
	controlledTank->SetRightThrottle(-amount);
}


