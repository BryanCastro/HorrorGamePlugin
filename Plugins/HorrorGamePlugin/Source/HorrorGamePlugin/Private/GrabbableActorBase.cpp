// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabbableActorBase.h"
#include "GameUtils.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AGrabbableActorBase::AGrabbableActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

}

// Called when the game starts or when spawned
void AGrabbableActorBase::BeginPlay()
{
	Super::BeginPlay();
	PlayerRef = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (!PlayerRef)
		GameUtils::LogMessage("PhysicsDoor.cpp: Failed to Get Reference to Player");


}

// Called every frame
void AGrabbableActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrabbableActorBase::Grabbed(FVector2D Axis) {

}