// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementComp.h"
#include "GameUtils.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UMovementComp::UMovementComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMovementComp::BeginPlay()
{
	Super::BeginPlay();

	GameUtils::LogMessage("MovementComp.cpp: MovementComp is Active!", FColor::Green, 100);

	// ...
	
}


// Called every frame
void UMovementComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMovementComp::Initialize(ACharacter* OwningCharacter) {

	if (OwningCharacter) {
		OwningCharacterRef = OwningCharacter;
		OwningCharacterMovementCompRef=OwningCharacterRef->GetCharacterMovement();
		if (OwningCharacterMovementCompRef) {
			OwningCharacterMovementCompRef->MaxWalkSpeed = WalkSpeed;
			PlayerCapsuleHeight=OwningCharacterRef->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		}
		else
			GameUtils::LogMessage("MovementComp.cpp: OwningCharacterMovementCompRef is nullptr");

	}
	else
		GameUtils::LogMessage("MovementComp.cpp: OwningCharacterRef is nullptr");
}


void UMovementComp::StartSprint() {


	if (CurrentStamina > MinStamina && OwningCharacterMovementCompRef->Velocity.Length() > 0) {
		OwningCharacterMovementCompRef->MaxWalkSpeed = SprintSpeed;
		GetWorld()->GetTimerManager().ClearTimer(RegenerateStaminaHandle);
		GetWorld()->GetTimerManager().SetTimer(SprintTimerHandle, this, &UMovementComp::SprintTimer, SprintDrainageTime, true, SprintStartDelay);
	}
}

void UMovementComp::StopSprint() {
	GetWorld()->GetTimerManager().ClearTimer(SprintTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(RegenerateStaminaHandle, this, &UMovementComp::RegenerateStaminaTimer, SprintRecoveryTime, true, SprintRecoveryDelay);
	OwningCharacterMovementCompRef->MaxWalkSpeed = WalkSpeed;
	GameUtils::LogMessage("MovementComp.cpp: StopTimer Function Working!", FColor::Yellow);
}

void UMovementComp::SprintTimer() {
	if (OwningCharacterMovementCompRef->Velocity.Length() > 0) {
		CurrentStamina = FMath::Clamp(--CurrentStamina, MinStamina, MaxStamina);
		if (CurrentStamina <= MinStamina) {
			StopSprint();
		}
	}
	else
		StopSprint();

	GameUtils::LogMessage(FString::Printf(TEXT("MovementComp.cpp: Current Stamina: %f"), CurrentStamina));
}

void UMovementComp::RegenerateStaminaTimer() {
	CurrentStamina = FMath::Clamp(++CurrentStamina, MinStamina, MaxStamina);
	if (CurrentStamina >= MaxStamina) {
		GetWorld()->GetTimerManager().ClearTimer(RegenerateStaminaHandle);
	}
	GameUtils::LogMessage(FString::Printf(TEXT("MovementComp.cpp: Current Stamina: %f"), CurrentStamina), FColor::Green);
}

void UMovementComp::ToggleCrouch(bool bShouldCrouch)
{

	bIsCrouching = bShouldCrouch;

	if(bShouldCrouch)
	{
		StopSprint();
		CurrentCrouchTime = 0;
		OwningCharacterMovementCompRef->MaxWalkSpeed = CrouchSpeed;
		GetWorld()->GetTimerManager().ClearTimer(CrouchUpHandle);
		GetWorld()->GetTimerManager().SetTimer(CrouchDownHandle, this, &UMovementComp::CrouchDown, 0.01f, true, 0.0f);
	}
	else
	{
		CurrentCrouchTime = 0;
		OwningCharacterMovementCompRef->MaxWalkSpeed = WalkSpeed;
		GetWorld()->GetTimerManager().ClearTimer(CrouchDownHandle);
		GetWorld()->GetTimerManager().SetTimer(CrouchUpHandle, this, &UMovementComp::CrouchUp, 0.01f, true, 0.0f);
	}
}

void UMovementComp::CrouchDown()
{

	if(CrouchFloatCurve)
	{
		CurrentCrouchTime += GetWorld()->GetDeltaSeconds();
		// Calculate the alpha value based on the current time and total duration
		float Alpha = FMath::Clamp(CurrentCrouchTime / CrouchLerpDuration, 0.0f, 1.0f);
		float CurveValue = CrouchFloatCurve->GetFloatValue(Alpha);
		float InterpolatedValue = FMath::Lerp(PlayerCapsuleHeight, CrouchHalfHeight, CurveValue);
		OwningCharacterRef->GetCapsuleComponent()->SetCapsuleHalfHeight(InterpolatedValue);

		if(CurrentCrouchTime >= CrouchLerpDuration)
		{
			GetWorld()->GetTimerManager().ClearTimer(CrouchDownHandle);
			GameUtils::LogMessage("MovementComp.cpp: Crouch Lerp Complete");
			CurrentCrouchTime = 0;
		}
	}
	else
	{
		GameUtils::LogMessage("MovementComp.cpp: Failed to Find a CrouchFloatCurve!");
	}


}

void UMovementComp::CrouchUp()
{

	if(CrouchFloatCurve)
	{
		CurrentCrouchTime += GetWorld()->GetDeltaSeconds();
		// Calculate the alpha value based on the current time and total duration
		float Alpha = FMath::Clamp(CurrentCrouchTime / CrouchLerpDuration, 0.0f, 1.0f);
		float CurveValue = CrouchFloatCurve->GetFloatValue(Alpha);
		float InterpolatedValue = FMath::Lerp(CrouchHalfHeight, PlayerCapsuleHeight, CurveValue);
		OwningCharacterRef->GetCapsuleComponent()->SetCapsuleHalfHeight(InterpolatedValue);

		if (CurrentCrouchTime >= CrouchLerpDuration)
		{
			GetWorld()->GetTimerManager().ClearTimer(CrouchUpHandle);
			GameUtils::LogMessage("MovementComp.cpp: Stand Up Lerp Complete");
			CurrentCrouchTime = 0;
		}
	}
	else
	{
		GameUtils::LogMessage("MovementComp.cpp: Failed to Find a CrouchFloatCurve!");
	}

}