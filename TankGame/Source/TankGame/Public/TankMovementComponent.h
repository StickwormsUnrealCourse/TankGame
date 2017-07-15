// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class ATank;

UCLASS()
class TANKGAME_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float amount);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UStaticMeshComponent* bodyToSet);

private:
	UStaticMeshComponent* body;
	ATank* controlledTank;

};
