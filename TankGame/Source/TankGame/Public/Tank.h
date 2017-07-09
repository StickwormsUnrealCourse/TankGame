// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Projectile.h"
#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//class AProjetile;
//class TankAimingComponent;

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

	float maxThrottleForce = 100000000.0f;	//Theres two of these for each track 
};
