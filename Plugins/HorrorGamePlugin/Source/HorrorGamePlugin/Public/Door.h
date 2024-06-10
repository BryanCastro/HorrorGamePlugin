// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActorBase.h"
#include "Components/TimelineComponent.h"
#include "Door.generated.h"


class UStatiMeshComponent;
class UCurveFloat;
class UCurveVector;

/**
 * 
 */
UCLASS()
class HORRORGAMEPLUGIN_API ADoor : public AInteractiveActorBase
{
	GENERATED_BODY()
public:
	ADoor();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mesh")
	UStaticMeshComponent* DoorFrame;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mesh")
	UStaticMeshComponent* Door;
	
	virtual void Interact() override;

	UPROPERTY(EditAnywhere, Category="Timeline")
	UCurveFloat* FloatCurve;

	UFUNCTION()
	void TimelineUpdate(float Value);

	UFUNCTION()
	void TimelineFinished();


protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	UTimelineComponent* OpenTimeline;

	FOnTimelineFloat UpdateFunctionFloat;
	FOnTimelineEvent FinishedFunction;

	UPROPERTY(EditAnywhere, Category="Timeline", meta=(AllowPrivateAccess="true"))
	float PlayRate=1.0f;

	UPROPERTY(EditAnywhere, Category = "Timeline", meta = (AllowPrivateAccess = "true"))
	float DoorRotationDegrees = 90.0f;
	
	UPROPERTY(EditAnywhere, Category = "Timeline", meta = (AllowPrivateAccess = "true"))
	bool bIsDoorClosed = true;

};
