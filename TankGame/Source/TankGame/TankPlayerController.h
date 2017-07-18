#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"	//Must be last include

class ATank;
class UTankAimingComponent;

UCLASS()
class TANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	void AimTowardsCrossHair();
	bool GetSightRayHitLocation(FVector& hitLocation) const;

	UPROPERTY(EditDefaultsOnly)
	float crosshairXLoc = 0.5f;
	UPROPERTY(EditDefaultsOnly)
	float crosshairYLoc = 0.3333f;
};
