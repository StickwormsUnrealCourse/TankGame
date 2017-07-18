#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState :uint8
{
	Reloading,
	Aiming,
	Locked
};

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

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState firingState = EFiringState::Reloading;

private:
	UStaticMeshComponent* barrel = nullptr;
	
	UStaticMeshComponent* turret = nullptr;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void MoveBarrelTowards(FVector aimDirection);

	void ElevateBarrel(float relativeSpeed); //degrees per second

	void RotateTurret(float relativeSpeed); //degrees per second

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float elevationSpeed = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float maxElevation = 40.0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float minElevation = .0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float turretRotationSpeed = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float maxTurretRotation = 360.0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float minTurretRotation = .0f;



};
