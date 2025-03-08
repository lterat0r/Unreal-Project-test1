// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

class UInputMappingContext;
class UInputAction;

struct FInputActionValue;

class USphereComponent;

UCLASS()
class PROJECT1_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual void Attack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//测试用:
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "U|test")
	//float testLen;

	//UFUNCTION TEST
	UFUNCTION(BlueprintCallable)
	void CallableFunction();

	//纯函数必须有返回值，不然没意义
	UFUNCTION(BlueprintPure)
	bool PureFunction();


	//BlueprintImplementEvent
	UFUNCTION(BlueprintImplementableEvent)
	void MyblueprintFunction();

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	// 演示组合有bug
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sphere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> SphereComponent;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> PlayerCamera;

	//UPROPERTY TEST
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "U|test", meta = (AllowPrivateAccess = "true"))
	float testLen;

	// Input
	UPROPERTY(EditDefaultsOnly, Category = "Input")

	TObjectPtr<UInputMappingContext> DefaultMapping;

	UPROPERTY(EditDefaultsOnly, Category = "Input")

	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")

	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")

	TObjectPtr<UInputAction> AttackAction;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
