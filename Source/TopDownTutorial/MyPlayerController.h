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
	class UInputAction* MoveAction;
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

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
	/** Called for movement input */
	void Move(const struct FInputActionValue& Value);
	/** Called for looking input */
	void Look(const struct FInputActionValue& Value);

	void Jump();
	void StopJumping();
};
