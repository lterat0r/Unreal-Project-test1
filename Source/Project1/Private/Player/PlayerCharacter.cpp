// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
//#include "Components/SphereComponent.h";   // 有报错搞不懂为啥

#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>

// 这里是因为在PlayerCharacter.h中包含过GameFramework/Character.h了，所以不会报错，但是这里要包含的是另外一个头文件
// 但是由于有pragma once,所以多写一遍包含也无所谓
#include "GameFramework/CharacterMovementComponent.h" 

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->SetRelativeRotation(FRotator(-40.f, 0.f, 0.f)); // pitch yaw roll 
	// 如果你想修改
	// SetRootComponent(CameraBoom);
	// 相机附着到boom
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("Player Camera");
	PlayerCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// 有报错没高明白
	
	/*SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere Collision");
	SphereComponent->SetSphereRadius(35.f);*/
	

	// 相机附着到某一位置
	//PlayerCamera->SetupAttachment(GetMesh(), FName("RootSocket"));


	// 1不要让角色随着控制器旋转
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;

	// 2相机杆旋转 而相机不旋转
	CameraBoom->bUsePawnControlRotation = true;
	PlayerCamera->bUsePawnControlRotation = false;

	// 3角色要根据其运动方向进行旋转
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	UE_LOG(LogTemp, Warning, TEXT("APlayerCharacter::APlayerCharacter"));
	
}

void APlayerCharacter::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack from character"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("APlayerCharacter::BeginPlay"));
	Super::BeginPlay();
	//MyblueprintFunction();
	//UE_LOG(LogTemp, Warning, TEXT("CameraBoom : TargetArmLength: %f"), CameraBoom->TargetArmLength);
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, FString::Printf(TEXT("CameraBoom : TargetArmLength: %f"), CameraBoom->TargetArmLength));
	if (const ULocalPlayer* Player = (GEngine && GetWorld()) ? GEngine->GetFirstGamePlayer(GetWorld()) : nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player);
		if (DefaultMapping)
		{
			Subsystem->AddMappingContext(DefaultMapping, 0);
		}
	}
}

void APlayerCharacter::CallableFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("Callable"));
}

bool APlayerCharacter::PureFunction()
{
	return false;
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();
	if (Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, MoveVector.X);
		AddMovementInput(RightDirection, MoveVector.Y);
	}

}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();
	if (Controller)
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Attack);
	}

}

