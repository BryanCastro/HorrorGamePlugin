// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HorrorPlayerController.generated.h"


class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UInputComponent;
class APlayerCharacter;
/**
 * 
 */
UCLASS()
class HORRORGAMEPLUGIN_API AHorrorPlayerController : public APlayerController
{
	GENERATED_BODY()

	AHorrorPlayerController();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	float LookSensetivity = 4.0f;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputMappingContext* IMC_Player;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* LookAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* JumpAction;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UFUNCTION()
	bool SetActions(UEnhancedInputComponent* EnhancedInputComponent);

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump();

	UPROPERTY()
	APlayerCharacter* PlayerCharacterRef;
};
