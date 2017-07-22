#pragma once

#include "GameFramework/ProjectileMovementComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

//class UProjectileMovementComponent;

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

};
