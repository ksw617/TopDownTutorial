// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "MyPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyPlayerController::AMyPlayerController()
{
}

void AMyPlayerController::BeginPlay()
{

	Super::BeginPlay();

}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMyPlayerController::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyPlayerController::StopJumping);


		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Move);
		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Look);

	}
}

void AMyPlayerController::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();


	// find out which way is forward
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	// get right vector
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	APawn* ControlledPawn = GetPawn();

	// add movement 
	ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
	ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);



}

void AMyPlayerController::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	APawn* ControlledPawn = GetPawn();

	// add yaw and pitch input to controller
	ControlledPawn->AddControllerYawInput(LookAxisVector.X);
	ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);

}

void AMyPlayerController::Jump()
{
	AMyPlayer* MyPlayer = Cast<AMyPlayer>(GetPawn());
	MyPlayer->Jump();
}

void AMyPlayerController::StopJumping()
{
	auto* MyPlayer = Cast<AMyPlayer>(GetPawn());
	MyPlayer->StopJumping();
}
