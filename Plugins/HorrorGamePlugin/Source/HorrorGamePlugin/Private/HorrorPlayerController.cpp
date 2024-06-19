// Fill out your copyright notice in the Description page of Project Settings.

#include "HorrorPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameUtils.h"
#include "PlayerCharacter.h"
#include "InteractiveActorBase.h"
#include "GrabbableActorBase.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "MovementComp.h"
#include "Curves/CurveFloat.h" // Include for UCurveFloat


AHorrorPlayerController::AHorrorPlayerController() {

	//static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_Player(TEXT("InputMappingContext''"));
	
}

void AHorrorPlayerController::BeginPlay() {
	Super::BeginPlay();

	PlayerCharacterRef = Cast<APlayerCharacter>(GetPawn());
	if (!PlayerCharacterRef)
		GameUtils::LogMessage("HorrorPlayerController.cpp: Failed to Get Ref to PlayerCharacter");
	GrabbedActorRef = nullptr;

	Initialize();
}

void AHorrorPlayerController::Initialize() {
	if (MainWidgetClass) {
		UUserWidget* MainWidget = CreateWidget<UUserWidget>(this, MainWidgetClass);
		if (MainWidget) {
			MainWidget->AddToViewport();
		}
		else
			GameUtils::LogMessage("HorrorPlayerController.cpp: Failed to Add Widget to Viewport");
	}
	else
		GameUtils::LogMessage("HorrorPlayerController.cpp: Failed to Load MainWidgetClass");
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
	if (InteractAction)
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AHorrorPlayerController::Interact);
	else
		success=false;
	if (GrabAction) {
		EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Started, this, &AHorrorPlayerController::GrabActor);
		EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Completed, this, &AHorrorPlayerController::ReleaseGrabbedActor);
	}
	else
		success = false;
	if (MoveDoorAction)
		EnhancedInputComponent->BindAction(MoveDoorAction, ETriggerEvent::Triggered, this, &AHorrorPlayerController::HandleGrabbedActor);
	else
		success = false;
	if (FlashLightToggleAction)
		EnhancedInputComponent->BindAction(FlashLightToggleAction, ETriggerEvent::Started, this, &AHorrorPlayerController::HandleFlashLightOn);
	else
		success = false;
	if (SprintAction) {
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AHorrorPlayerController::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AHorrorPlayerController::StopSprint);
	}
	else
		success = false;
	if (CrouchToggleAction)
		EnhancedInputComponent->BindAction(CrouchToggleAction, ETriggerEvent::Started, this, &AHorrorPlayerController::HandleCrouch);
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

void AHorrorPlayerController::Interact() {

	
	AActor* HitActor=PlayerCharacterRef->LineTrace(300.0f);

	if (HitActor) {
		AInteractiveActorBase* InteractiveActor=Cast<AInteractiveActorBase>(HitActor);
		if (InteractiveActor) {
			GameUtils::LogMessage(FString::Printf(TEXT("HorrorPlayerController.cpp: Hit Actor is : %s"), *HitActor->GetName()), FColor::Green);
			PlayerCharacterRef->DisplayDebugLine(true, 300.0f, HitActor->GetActorLocation());
			InteractiveActor->Interact();
		}
		else {
			PlayerCharacterRef->DisplayDebugLine(false, 300.0f, HitActor->GetActorLocation());
			GameUtils::LogMessage("HorrorPlayerController.cpp: Non Interactive Actor Hit");
		}
	}
}

void AHorrorPlayerController::GrabActor(const FInputActionValue& Value) {
	AActor* HitActor = PlayerCharacterRef->LineTrace(300.0f);
	if (HitActor) {
		AGrabbableActorBase* GrabbableActor = Cast<AGrabbableActorBase>(HitActor);
		if (GrabbableActor) {
			GrabbedActorRef = GrabbableActor;
			GameUtils::LogMessage(FString::Printf(TEXT("HorrorPlayerController.cpp: Grab Actor is : %s"), *HitActor->GetName()), FColor::Green);
			PlayerCharacterRef->DisplayDebugLine(true, 300.0f, HitActor->GetActorLocation());
			PlayerCharacterRef->GetCharacterMovement()->DisableMovement();
			SetIgnoreLookInput(true);
			bIsGrabbingActor=true;
		}
		else {
			PlayerCharacterRef->DisplayDebugLine(false, 300.0f, HitActor->GetActorLocation());
			GameUtils::LogMessage("HorrorPlayerController.cpp: Non Interactive Grab Actor Hit");
		}
	}


}

void AHorrorPlayerController::HandleGrabbedActor(const FInputActionValue& Value) {

	if (GrabbedActorRef) {
		const FVector2D Axis = Value.Get<FVector2D>();
		GrabbedActorRef->Grabbed(Axis);
	}
}

void AHorrorPlayerController::ReleaseGrabbedActor(const FInputActionValue& Value) {
	GrabbedActorRef = nullptr;
	bIsGrabbingActor = false;
	SetIgnoreLookInput(false);
	PlayerCharacterRef->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking, 0);

}

void AHorrorPlayerController::HandleFlashLightOn(const FInputActionValue& Value) {
	if (bIsFlashLightOn)
		PlayerCharacterRef->TurnOnFlashLight(false);
	else
		PlayerCharacterRef->TurnOnFlashLight(true);

	bIsFlashLightOn = !bIsFlashLightOn;
}
void AHorrorPlayerController::StartSprint(const FInputActionValue& Value){
	if (PlayerCharacterRef)
	{
		if (bIsCrouching)
			HandleCrouch(Value);
		PlayerCharacterRef->GetMovementComp()->StartSprint();
	}

}

void AHorrorPlayerController::StopSprint(const FInputActionValue& Value){
	if (PlayerCharacterRef)
		PlayerCharacterRef->GetMovementComp()->StopSprint();
}

void AHorrorPlayerController::HandleCrouch(const FInputActionValue& Value)
{
	bIsCrouching = !bIsCrouching;
	if(PlayerCharacterRef)
	{
		PlayerCharacterRef->GetMovementComp()->ToggleCrouch(bIsCrouching);
	}

}