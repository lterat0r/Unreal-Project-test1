// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnime.generated.h"


class APlayerCharacter;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class PROJECT1_API UPlayerAnime : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerCharacter> PlayerCharacter;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UCharacterMovementComponent> PlayerCharacterMovement;

	UPROPERTY(BlueprintReadOnly)
	float Speed;
};
