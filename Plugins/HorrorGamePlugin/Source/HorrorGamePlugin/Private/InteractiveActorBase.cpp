// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveActorBase.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameUtils.h"

// Sets default values
AInteractiveActorBase::AInteractiveActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractiveActorBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if (!PlayerRef)
		GameUtils::LogMessage("InteractiveActorBase.cpp: Failed to Get Reference to Player");
		
}

// Called every frame
void AInteractiveActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractiveActorBase::Interact() {

}