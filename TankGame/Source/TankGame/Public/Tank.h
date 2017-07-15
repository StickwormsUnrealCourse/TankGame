#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class AProjectile;
class UTankAimingComponent;
class UTankMovementComponent;

UCLASS()
class TANKGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelRef(UStaticMeshComponent* barrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretRef(UStaticMeshComponent* turretToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBodyRef(UStaticMeshComponent* bodyToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	UFUNCTION(BlueprintCallable, Category = Input)
	void SetLeftThrottle(float throttle);

	UFUNCTION(BlueprintCallable, Category = Input)
	void SetRightThrottle(float throttle);

	void AimAt(FVector hitLocation);

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:

	ATank();
	
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float launchSpeed = 100000;//TODO find sensible default

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> projectile_BP;

	UStaticMeshComponent* barrel;
	UStaticMeshComponent* body;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float reloadTime = 3.0f;

	double lastFiredTimeStamp = 0;

	float maxThrottleForce = 50000000.0f;	//Theres two of these for each track 
};
