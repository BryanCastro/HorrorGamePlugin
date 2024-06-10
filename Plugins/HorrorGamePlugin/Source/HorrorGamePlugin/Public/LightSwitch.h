// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActorBase.h"
#include "LightSwitch.generated.h"


class UStaticMeshComponent;
class ALight;
class ULightComponent;

/**
 * 
 */
UCLASS()
class HORRORGAMEPLUGIN_API ALightSwitch : public AInteractiveActorBase
{
	GENERATED_BODY()
	
public:
	ALightSwitch();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Switch Settings")
	UStaticMeshComponent* LightSwitchMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Switch Settings")
	ALight* LinkedLightRef;

	virtual void Interact() override;

protected:
	UPROPERTY()
	ULightComponent* LightComponent;
};
