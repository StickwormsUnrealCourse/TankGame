#pragma once


//#include "ParticleDefinitions.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

//class UProjectileMovementComponent;
//class UParticleSystemComponent;


UCLASS()
class TANKGAME_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float speed);

protected:
	virtual void BeginPlay() override;

private:
	UProjectileMovementComponent* projectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* collisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* launchBlast = nullptr;

};
