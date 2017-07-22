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

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UStaticMeshComponent* bodyToSet);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float amount);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float amount);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetLeftThrottle(float throttle);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetRightThrottle(float throttle);

private:
	UStaticMeshComponent* body = nullptr;

	//Called from pathfinding on AI Controller
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	float maxThrottleForce = 50000000.0f;	//Theres two of these for each track 
};
