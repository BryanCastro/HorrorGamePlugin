// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlickeringLight.generated.h"

class UPointLightComponent;

UCLASS()
class HORRORGAMEPLUGIN_API AFlickeringLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlickeringLight();

	virtual void OnConstruction(const FTransform& Transform) override;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flickering Light")
	float MinTime=0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flickering Light")
	float MaxTime=0.3f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flickering Light")
	float MinFlickerIntensity=3500.0f;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Flickering Light")
	UPointLightComponent* PointLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Flickering Light")
	float MaxIntensity = 5000;

	bool bIsFlipped = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle TimerHandle_RetriggerableDelay;
	void OnDelayComplete();
};
