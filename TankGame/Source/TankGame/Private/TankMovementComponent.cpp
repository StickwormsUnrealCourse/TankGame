/*
Inherits from NavMovementComp
Sets refs to: body and controlledTank
Overrides RequestDirectMove to utilise:
IntendMoveForward and IntendTurnRight to set the throttles on the tank.
*/

#include "TankMovementComponent.h"


/*
UTankMovementComponent::UTankMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}
*/

void UTankMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTankMovementComponent::OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("HIT: %s %f"), *(otherActor->GetName()), FPlatformTime::Seconds());

	//TODO This is hidious
	SetLeftTrackForce();
	SetRightTrackForce();
	CancelOutSideWaysMovement();
	currentLeftThrottle = 0;
	currentRightThrottle = 0;
}


void UTankMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	//Super::TickComponent();
}

void UTankMovementComponent::CancelOutSideWaysMovement()
{
	//Prevent sideways movement of the tank
	//Movement to the right side
	auto root = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto slippageSpeed = FVector::DotProduct(root->GetRightVector(), root->GetComponentVelocity());

	//Acceleration required this frame to correct sideways movement
	auto deltaTime = GetWorld()->GetDeltaSeconds();
	auto correctionAcceleration = -slippageSpeed / deltaTime * root->GetRightVector();

	//Force required to correct (F = ma)
	auto correctionForce = (root->GetMass() * correctionAcceleration) / 2.0f; //Two Tracks
	root->AddForce(correctionForce);
}

void UTankMovementComponent::Initialise(UStaticMeshComponent* bodyToSet)
{
	body = bodyToSet;

	//Setup hit events for the body of the tank so we can shut off driving force when in air
	if (!ensure(body)) { return; }
	body->OnComponentHit.AddDynamic(this, &UTankMovementComponent::OnHit);
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
	currentLeftThrottle = FMath::Clamp<float>(currentLeftThrottle + throttle, -1, 1);
}

void UTankMovementComponent::SetRightThrottle(float throttle)
{
	currentRightThrottle = FMath::Clamp<float>(currentRightThrottle + throttle, -1, 1);
}

void UTankMovementComponent::SetLeftTrackForce()
{
	//UE_LOG(LogTemp, Warning, TEXT("Left Track: %f"), throttle);

	if (!ensure(body)) { return; }

	auto forceApplied = body->GetForwardVector() * currentLeftThrottle * maxThrottleForce;
	auto forceLocation = body->GetSocketLocation("LTrack");
	body->AddForceAtLocation(forceApplied, forceLocation);

}

void UTankMovementComponent::SetRightTrackForce()
{
	//UE_LOG(LogTemp, Warning, TEXT("Right Track: %f"), throttle);

	if (!ensure(body)) { return; }

	auto forceApplied = body->GetForwardVector() * currentRightThrottle * maxThrottleForce;
	auto forceLocation = body->GetSocketLocation("RTrack");
	body->AddForceAtLocation(forceApplied, forceLocation);
}


