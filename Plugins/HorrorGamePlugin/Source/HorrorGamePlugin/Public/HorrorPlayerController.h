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
class UUserWidget;
class AGrabbableActorBase;
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* InteractAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* GrabAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveDoorAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* FlashLightToggleAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* SprintAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* CrouchToggleAction;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UFUNCTION()
	bool SetActions(UEnhancedInputComponent* EnhancedInputComponent);

	UFUNCTION()
	void Initialize();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> MainWidgetClass;

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump();
	void Interact();
	void GrabActor(const FInputActionValue& Value);
	void HandleGrabbedActor(const FInputActionValue& Value);
	void ReleaseGrabbedActor(const FInputActionValue& Value);
	void HandleFlashLightOn(const FInputActionValue& Value);
	void StartSprint(const FInputActionValue& Value);
	void StopSprint(const FInputActionValue& Value);
	void HandleCrouch(const FInputActionValue& Value);

	bool bIsGrabbingActor = false;
	bool bIsFlashLightOn = true;
	bool bIsCrouching = false;

	UPROPERTY()
	AGrabbableActorBase* GrabbedActorRef;

	UPROPERTY()
	APlayerCharacter* PlayerCharacterRef;


};
