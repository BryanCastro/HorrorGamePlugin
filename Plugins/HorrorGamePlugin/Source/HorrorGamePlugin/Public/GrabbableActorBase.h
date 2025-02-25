// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrabbableActorBase.generated.h"

class APlayerCharacter;


UCLASS()
class HORRORGAMEPLUGIN_API AGrabbableActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrabbableActorBase();
	virtual void Grabbed(FVector2D Axis);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	APlayerCharacter* PlayerRef;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
