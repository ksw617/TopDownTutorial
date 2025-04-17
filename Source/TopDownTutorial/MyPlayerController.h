// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNTUTORIAL_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationClickAction;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	
private:
	AMyPlayerController();

protected:
	virtual void BeginPlay() override;
	// Called to bind functionality to input
	virtual void SetupInputComponent() override;
protected:
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();

private:
	FVector CachedDestination;
	float FollowTime;

	bool bMousePressed = false;

};
