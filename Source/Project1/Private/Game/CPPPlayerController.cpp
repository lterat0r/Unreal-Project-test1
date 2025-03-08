// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CPPPlayerController.h"

void ACPPPlayerController::OnPossess(APawn* InPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("ACPPPlayerController::OnPossess"));
	Super::OnPossess(InPawn);
	if (InPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pawn OnPossess"));
		InPawn->SetActorLocation(FVector(0.f, 0.f, 0.f));
	}
}
