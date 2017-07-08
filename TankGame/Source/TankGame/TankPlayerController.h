// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"	//Must be last include

class ATank;

UCLASS()
class TANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;


private:
	void AimTowardsCrossHair();
	bool GetSightRayHitLocation(FVector& hitLocation) const;

	UPROPERTY(EditAnywhere)
	float crosshairXLoc = 0.5f;
	UPROPERTY(EditAnywhere)
	float crosshairYLoc = 0.3333f;
};
