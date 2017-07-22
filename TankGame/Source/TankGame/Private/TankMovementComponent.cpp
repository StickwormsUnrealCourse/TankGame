/*
Inherits from NavMovementComp
Sets refs to: body and controlledTank
Overrides RequestDirectMove to utilise:
IntendMoveForward and IntendTurnRight to set the throttles on the tank.
*/

#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UStaticMeshComponent* bodyToSet)
{
	body = bodyToSet;
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

	if (!ensure(body)) { return; }

	SetLeftThrottle(amount);
	SetRightThrottle(amount);
}

void UTankMovementComponent::IntendTurnRight(float amount)
{
	//UE_LOG(LogTemp, Warning, TEXT("IntendMoveRight: %f"), amount);

	if (!ensure(body)) { return; }

	SetLeftThrottle(amount);
	SetRightThrottle(-amount);
}

void UTankMovementComponent::SetLeftThrottle(float throttle)
{
	//UE_LOG(LogTemp, Warning, TEXT("Left Throttle: %f"), throttle);

	if (!ensure(body)) { return; }

	auto forceApplied = body->GetForwardVector() * throttle * maxThrottleForce;
	auto forceLocation = body->GetSocketLocation("LTrack");
	body->AddForceAtLocation(forceApplied, forceLocation);

}

void UTankMovementComponent::SetRightThrottle(float throttle)
{
	//UE_LOG(LogTemp, Warning, TEXT("Right Throttle: %f"), throttle);

	if (!ensure(body)) { return; }

	auto forceApplied = body->GetForwardVector() * throttle * maxThrottleForce;
	auto forceLocation = body->GetSocketLocation("RTrack");
	body->AddForceAtLocation(forceApplied, forceLocation);
}


