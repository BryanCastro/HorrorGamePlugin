// Fill out your copyright notice in the Description page of Project Settings.


#include "FlickeringLight.h"
#include "Components/PointLightComponent.h"
#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"


// Sets default values
AFlickeringLight::AFlickeringLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
}

void AFlickeringLight::OnConstruction(const FTransform& Transform) {
	PointLight->SetIntensity(MaxIntensity);
}

// Called when the game starts or when spawned
void AFlickeringLight::BeginPlay()
{
	Super::BeginPlay();

	float DelayDuration = FMath::FRandRange(MinTime, MaxTime);
	GetWorldTimerManager().SetTimer(TimerHandle_RetriggerableDelay, this, &AFlickeringLight::OnDelayComplete, DelayDuration);	
}

// Called every frame
void AFlickeringLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFlickeringLight::OnDelayComplete() {
	if (bIsFlipped)
		PointLight->SetIntensity(MinFlickerIntensity);
	else
		PointLight->SetIntensity(MaxIntensity);

	bIsFlipped = !bIsFlipped;

	float DelayDuration = FMath::FRandRange(MinTime, MaxTime);
	// Reset the timer to retrigger the delay
	GetWorldTimerManager().SetTimer(TimerHandle_RetriggerableDelay, this, &AFlickeringLight::OnDelayComplete, DelayDuration, false);
}

