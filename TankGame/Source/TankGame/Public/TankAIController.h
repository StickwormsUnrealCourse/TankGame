#pragma once


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

	virtual	void ATankAIController::SetPawn(APawn* InPawn) override;

	UTankAimingComponent* aimingComponent = nullptr;

	UFUNCTION()
	void OnTankDeath();

};
