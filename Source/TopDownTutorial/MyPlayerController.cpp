// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "MyPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraFunctionLibrary.h"



AMyPlayerController::AMyPlayerController()
{
	//마우스 커서를 보이도록 설정
	bShowMouseCursor = true;
	//기본 마우스 커서 모양 설정
	DefaultMouseCursor = EMouseCursor::Default;
	//캐시된 목적지 벡터를 초기화 (월드 좌표의 시작점)
	CachedDestination = FVector::ZeroVector;
	//누름 지속 시간을 0으로 초기화
	FollowTime = 0.f;

	
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
		// SetDestinationClickAction
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AMyPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AMyPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AMyPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AMyPlayerController::OnSetDestinationReleased);
		

	}
}

void AMyPlayerController::OnInputStarted()
{
	StopMovement();
}

void AMyPlayerController::OnSetDestinationTriggered()
{
	FollowTime += GetWorld()->GetDeltaSeconds();

	FHitResult Hit;

	bool bHitSuccessful = false;

	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);

	}

}

void AMyPlayerController::OnSetDestinationReleased()
{
	if (FollowTime <= ShortPressThreshold)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination);
	
	}

	FollowTime = 0.f;
}
