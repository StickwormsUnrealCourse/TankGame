// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "Tank.h"

void UTankMovementComponent::Initialise(UStaticMeshComponent* bodyToSet)
{
	auto controlledTank = Cast<ATank>(GetPawn());
	body = bodyToSet;
}

void UTankMovementComponent::IntendMoveForward(float amount)
{
	UE_LOG(LogTemp, Warning, TEXT("IntendMoveForward: %f"), amount);

	if (!body) { return; }



}
