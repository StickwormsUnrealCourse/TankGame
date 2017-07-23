#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float acceptanceRadius = 5000;

private:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	UTankAimingComponent* aimingComponent = nullptr;

};
