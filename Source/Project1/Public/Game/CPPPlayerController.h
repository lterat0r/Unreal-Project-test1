// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPPPlayerController.generated.h"

/**
 *  Player() -> Onpossess() -> Player -> beginplay()
 *  
 *  HUD
 */
UCLASS()
class PROJECT1_API ACPPPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void OnPossess(APawn* InPawn) override;
};
