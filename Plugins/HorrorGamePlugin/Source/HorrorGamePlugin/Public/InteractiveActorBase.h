// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractiveActorBase.generated.h"

class APlayerCharacter;

UCLASS()
class HORRORGAMEPLUGIN_API AInteractiveActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveActorBase();

	UFUNCTION()
	virtual void Interact();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	APlayerCharacter* PlayerRef;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
