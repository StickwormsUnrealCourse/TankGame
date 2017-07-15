#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class ATank;

UCLASS()
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

private:
	UStaticMeshComponent* body = nullptr;
	ATank* controlledTank = nullptr;

	//Called from pathfinding on AI Controller
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
};
