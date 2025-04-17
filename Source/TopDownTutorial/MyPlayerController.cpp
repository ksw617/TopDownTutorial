// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "MyPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyPlayerController::AMyPlayerController()
{
	//���콺 Ŀ���� ���̵��� ����
	bShowMouseCursor = true;
	//�⺻ ���콺 Ŀ�� ��� ����
	DefaultMouseCursor = EMouseCursor::Default;
	//ĳ�õ� ������ ���͸� �ʱ�ȭ (���� ��ǥ�� ������)
	CachedDestination = FVector::ZeroVector;
	//���� ���� �ð��� 0���� �ʱ�ȭ
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
	UE_LOG(LogTemp, Log, TEXT("OnInputStarted"));
}

void AMyPlayerController::OnSetDestinationTriggered()
{
	UE_LOG(LogTemp, Log, TEXT("OnSetDestinationTriggered"));
}

void AMyPlayerController::OnSetDestinationReleased()
{
	UE_LOG(LogTemp, Log, TEXT("OnSetDestinationReleased"));
}
