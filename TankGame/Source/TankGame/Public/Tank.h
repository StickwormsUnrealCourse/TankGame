// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class TANKGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector hitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelRef(UStaticMeshComponent* barrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretRef(UStaticMeshComponent* turretToSet);

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

private:

	ATank();
	
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
	float launchSpeed = 100000;//TODO find sensible default
};
