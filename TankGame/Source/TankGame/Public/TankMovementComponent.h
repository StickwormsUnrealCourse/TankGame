#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

//class ATank;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKGAME_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:

	//UTankMovementComponent();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UStaticMeshComponent* bodyToSet);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float amount);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float amount);


private:

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UStaticMeshComponent* body = nullptr;

	//Called from pathfinding on AI Controller
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	float maxThrottleForce = 50000000.0f;	//Theres two of these for each track 

	void CancelOutSideWaysMovement();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hit);

	float currentLeftThrottle = 0.0f;
	float currentRightThrottle = 0.0f;
	void SetLeftThrottle(float throttle);
	void SetRightThrottle(float throttle);
	void SetLeftTrackForce();
	void SetRightTrackForce();

};
