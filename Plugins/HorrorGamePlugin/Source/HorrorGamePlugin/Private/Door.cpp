// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "GameUtils.h"
#include "Curves/CurveFloat.h"
#include "Curves/CurveVector.h"
#include "UObject/ConstructorHelpers.h"
#include "PlayerCharacter.h"


ADoor::ADoor() : AInteractiveActorBase(){

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));

	RootComponent = DoorFrame;
	Door->SetupAttachment(DoorFrame);

	OpenTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("OpenTimeline"));

	UpdateFunctionFloat.BindUFunction(this, FName("TimelineUpdate"));
	FinishedFunction.BindUFunction(this, FName("TimelineFinished"));
}

void ADoor::BeginPlay() {
	Super::BeginPlay();

	if (!bIsDoorClosed) {
		float LastTime = FloatCurve->FloatCurve.GetLastKey().Time;
		float LastValue = FloatCurve->GetFloatValue(LastTime);

		OpenTimeline->SetNewTime(LastTime);
		OpenTimeline->SetPlaybackPosition(LastTime, false);

		TimelineUpdate(LastValue);
	}

	if (FloatCurve) {
		OpenTimeline->AddInterpFloat(FloatCurve, UpdateFunctionFloat);
		OpenTimeline->SetTimelineFinishedFunc(FinishedFunction);

		OpenTimeline->SetLooping(false);
		OpenTimeline->SetPlayRate(PlayRate);
	}
	else
		GameUtils::LogMessage("Door.cpp: Failed to Get a Reference to a Float Curve!");
	
}

void ADoor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (OpenTimeline) {
		OpenTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}
	else
			GameUtils::LogMessage("Door.cpp: Failed to Get a Reference to OpenTimeline!");
}

void ADoor::Interact() {
	Super::Interact();

	if (bIsDoorClosed) {
		FVector PlayerLocation = PlayerRef->GetActorLocation();
		FVector DoorLocation = GetActorLocation();
		FVector DistanceVector = DoorLocation - PlayerLocation;
		DistanceVector.Normalize();

		//Check Location Door is Pointing from Player using Dot Product
		FVector DoorForward = GetActorForwardVector();

		float DotProduct = FVector::DotProduct(DistanceVector, DoorForward);

		if (DotProduct >= 0)
			DoorRotationDegrees = 90.0f;
		else
			DoorRotationDegrees = -90.0f;
	}


	if(bIsDoorClosed)
		OpenTimeline->Play();
	else
		OpenTimeline->Reverse();

	bIsDoorClosed = !bIsDoorClosed;
}

void ADoor::TimelineUpdate(float Value){
	FRotator NewRotation = FRotator(0.0f, Value * DoorRotationDegrees, 0.0f);
	Door->SetRelativeRotation(NewRotation);
}

void ADoor::TimelineFinished(){
	GameUtils::LogMessage("Game.cpp: Timeline Finished Successfully!", FColor::Green);
}


