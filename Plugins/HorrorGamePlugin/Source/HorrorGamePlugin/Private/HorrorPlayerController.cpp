// Fill out your copyright notice in the Description page of Project Settings.

#include "HorrorPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"
#include "GameUtils.h"
#include "PlayerCharacter.h"

AHorrorPlayerController::AHorrorPlayerController() {

	//static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_Player(TEXT("InputMappingContext''"));
	
}

void AHorrorPlayerController::BeginPlay() {
	Super::BeginPlay();

	PlayerCharacterRef = Cast<APlayerCharacter>(GetPawn());
	if (!PlayerCharacterRef)
		GameUtils::LogMessage("HorrorPlayerController.cpp: Failed to Get Ref to PlayerCharacter");
}

void AHorrorPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent) {

			if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player)) {
				if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()) {
					if (IMC_Player) {
						InputSystem->AddMappingContext(IMC_Player, 1);
						if (SetActions(EnhancedInputComponent))
							GameUtils::LogMessage("HorrorPlayerController.cpp: Sucessfully Set all Input Actions", FColor::Green);
						else
							GameUtils::LogMessage("HorrorPlayerController.cpp: Failed to Set all Input Actions");
					}
					else
						GameUtils::LogMessage("HorrorPlayerController.cpp: Failed to load InputMappingContext");
				
				}
				else
					GameUtils::LogMessage("HorrorPlayerController.cpp: Failed to Get EnhancedInputLocalPlayerSubsystem");
			}
	}
	else
		GameUtils::LogMessage("HorrorPlayerController.cpp: Failed to Set Enhanced InputComponent");
}

bool AHorrorPlayerController::SetActions(UEnhancedInputComponent* EnhancedInputComponent) {
	bool success = true;
	if (LookAction)
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHorrorPlayerController::Look);
	else
		success = false;

	if (MoveAction)
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHorrorPlayerController::Move);
	else
		success = false;
	if (JumpAction)
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AHorrorPlayerController::Jump);
	else
		success = false;

	return success;
}

void AHorrorPlayerController::Move(const FInputActionValue& Value) {
	const FVector2D Axis = Value.Get<FVector2D>();

	if (PlayerCharacterRef) {
		PlayerCharacterRef->AddMovementInput(PlayerCharacterRef->GetActorForwardVector(), Axis.Y);
		PlayerCharacterRef->AddMovementInput(PlayerCharacterRef->GetActorRightVector(), Axis.X);
	}

}

void AHorrorPlayerController::Look(const FInputActionValue& Value){
	const FVector2D Axis = Value.Get<FVector2D>();

	AddPitchInput(Axis.Y* LookSensetivity);
	AddYawInput(Axis.X* LookSensetivity);
}

void AHorrorPlayerController::Jump() {
	PlayerCharacterRef->Jump();
}