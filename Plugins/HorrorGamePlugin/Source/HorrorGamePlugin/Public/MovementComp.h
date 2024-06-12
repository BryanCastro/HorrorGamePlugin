// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovementComp.generated.h"

class ACharacter;
class UCharacterMovementComponent;
struct FTimerHandle;


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

	UFUNCTION()
	void StartSprint();

	UFUNCTION()
	void StopSprint();


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
	void SprintTimer();
	void RegenerateStaminaTimer();
};
