#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"	//Must be last include

class UTankAimingComponent;
class ATank;

UCLASS()
class TANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void SetTankRef(ATank* tankRef);

private:
	void AimTowardsCrossHair();
	bool GetSightRayHitLocation(FVector& hitLocation) const;

	UPROPERTY(EditDefaultsOnly)
	float crosshairXLoc = 0.5f;
	UPROPERTY(EditDefaultsOnly)
	float crosshairYLoc = 0.3333f;

	UTankAimingComponent* aimingComponent = nullptr;
};
