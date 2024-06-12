// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpotLightComponent;
class USpringArmComponent;
class UMovementComp;

UCLASS()
class HORRORGAMEPLUGIN_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	APlayerCharacter();

	AActor* LineTrace(float Length);
	void DisplayDebugLine(bool success, float Length, FVector HitLocation);
	
	UFUNCTION()
	void TurnOnFlashLight(bool bTurnOnFlashLight);
	UMovementComp* GetMovementComp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Camera")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category="FlashLight")
	USpotLightComponent* FlashLight;

	UPROPERTY(EditAnywhere, Category="FlashLight")
	USpringArmComponent* FlashLightSpringArm;

	UPROPERTY(EditAnywhere, Category="Movement")
	UMovementComp* MovementComp;

	void Initialize();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
