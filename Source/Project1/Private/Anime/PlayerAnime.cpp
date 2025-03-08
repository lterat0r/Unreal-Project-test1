// Fill out your copyright notice in the Description page of Project Settings.


#include "Anime/PlayerAnime.h"
#include "Player/PlayerCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UPlayerAnime::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
	if (PlayerCharacter)
	{
		PlayerCharacterMovement = PlayerCharacter->GetCharacterMovement();
	}
}

void UPlayerAnime::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (PlayerCharacterMovement)
	{
		Speed = UKismetMathLibrary::VSizeXY(PlayerCharacterMovement->Velocity);
	}
}
