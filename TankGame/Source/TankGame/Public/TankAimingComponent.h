#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class AProjectile;

UENUM()
enum class EFiringState :uint8
{
	OutOfAmmo,
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

	void AimAt(FVector hitLocation);

	//New
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UStaticMeshComponent* barrelToSet, UStaticMeshComponent* turretToSet);
	
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	EFiringState GetFiringState();

	int GetAmmo();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState firingState = EFiringState::Reloading;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	int ammo = 3;


private:
	UStaticMeshComponent* barrel = nullptr;
	
	UStaticMeshComponent* turret = nullptr;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	bool IsBarrelMoving();

	bool IsReloaded();

	void MoveBarrelTowards(FVector aimDirection);

	void ElevateBarrel(float relativeSpeed); //degrees per second

	void RotateTurret(float relativeSpeed); //degrees per second

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float elevationSpeed = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float maxElevation = 40.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float minElevation = .0f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float turretRotationSpeed = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float maxTurretRotation = 360.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float minTurretRotation = .0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> projectile_BP;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float launchSpeed = 100000;//TODO find sensible default

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float reloadTime = 3.0f;

	double lastFiredTimeStamp = 0;

	FVector aimDir;



};
