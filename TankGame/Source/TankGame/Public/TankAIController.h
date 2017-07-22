#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

UCLASS()
class TANKGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	
	float acceptanceRadius = 3000;

	//New
	UTankAimingComponent* aimingComponent = nullptr;

};
