// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovementComp.generated.h"

class ACharacter;
class UCharacterMovementComponent;
struct FTimerHandle;
class UFloatCurve;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORGAMEPLUGIN_API UMovementComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovementComp();

	void Initialize(ACharacter* OwningCharacter);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float SprintSpeed=800.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float WalkSpeed = 400.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxStamina=100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MinStamina=0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintDrainageTime = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintStartDelay = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintRecoveryTime = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintRecoveryDelay = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crouch")
	float CrouchSpeed=200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crouch")
	float CrouchHalfHeight=44.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crouch")
	float CrouchLerpDuration= 0.5f;
	// Reference to the float curve
	UPROPERTY(EditAnywhere, Category = "Crouch")
	UCurveFloat* CrouchFloatCurve;


	UFUNCTION()
	void StartSprint();

	UFUNCTION()
	void StopSprint();
	UFUNCTION()
	void ToggleCrouch(bool bShouldCrouch);



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	ACharacter* OwningCharacterRef;
	UCharacterMovementComponent* OwningCharacterMovementCompRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CurrentStamina = MaxStamina;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FTimerHandle SprintTimerHandle;
	FTimerHandle RegenerateStaminaHandle;
	FTimerHandle CrouchUpHandle;
	FTimerHandle CrouchDownHandle;

	void SprintTimer();
	void RegenerateStaminaTimer();
	void CrouchDown();
	void CrouchUp();

	float PlayerCapsuleHeight;
	bool bIsCrouching=false;

	float CrouchStartTime = 0.0f;
	float CurrentCrouchTime = 0.0f;
	float CrouchEndValue = 1.0f; //value of last key in timeline curve aka at time CrouchLerpDuration, this should be 1
};
