// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UTankAimingComponent();

	virtual void BeginPlay() override;

	void SetBarrelRef(UStaticMeshComponent* barrelToSet);
	void SetTurretRef(UStaticMeshComponent* turretToSet);

	void AimAt(FVector hitLocation, float launchSpeed);

private:
	UStaticMeshComponent* barrel = nullptr;
	
	UStaticMeshComponent* turret = nullptr;

	void MoveBarrelTowards(FVector aimDirection);

	void ElevateBarrel(float relativeSpeed); //degrees per second

	void RotateTurret(float relativeSpeed); //degrees per second

	UPROPERTY(EditAnywhere, Category = Firing)
	float elevationSpeed = 5.0f;

	UPROPERTY(EditAnywhere, Category = Firing)
	float maxElevation = 40.0f;

	UPROPERTY(EditAnywhere, Category = Firing)
	float minElevation = .0f;

	UPROPERTY(EditAnywhere, Category = Firing)
	float turretRotationSpeed = 5.0f;

	UPROPERTY(EditAnywhere, Category = Firing)
	float maxTurretRotation = 360.0f;

	UPROPERTY(EditAnywhere, Category = Firing)
	float minTurretRotation = .0f;

};
