// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "Tank.h"



void UTankMovementComponent::Initialise(UStaticMeshComponent* bodyToSet)
{
	
	body = bodyToSet;
	

	//auto temp = GetOwner()->GetRootComponent();
	//UE_LOG(LogTemp, Warning, TEXT("Temp %s"), *temp->GetName());
	
	auto controlledTank = Cast<ATank>(GetOwner());
	UE_LOG(LogTemp, Warning, TEXT("Temp %s"), *controlledTank->GetName());

	
	/*
	controlledTank = Cast<ATank>(GetOwner()->GetRootComponent());
	UE_LOG(LogTemp, Warning, TEXT("Tank Component: %s"), *controlledTank->GetName());
	*/
}


void UTankMovementComponent::IntendMoveForward(float amount)
{
	UE_LOG(LogTemp, Warning, TEXT("IntendMoveForward: %f"), amount);

	
	if (!controlledTank) { return; }

	controlledTank->SetLeftThrottle(amount);
	controlledTank->SetRightThrottle(amount);
	
}
