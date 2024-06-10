// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSwitch.h"
#include "Engine/Light.h"
#include "Components/LightComponent.h"
#include "GameUtils.h"

ALightSwitch::ALightSwitch() {

	LightSwitchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightSwitchMesh"));

	LightSwitchMesh->SetupAttachment(RootComponent);
}

void ALightSwitch::BeginPlay() {
	if (LinkedLightRef) {
		LightComponent = LinkedLightRef->GetLightComponent();
	}
	else {
		GameUtils::LogMessage("LightSwitch.cpp: LinkedPointLightRef is Null");
	}

}

void ALightSwitch::Interact() {

	if (LightComponent) {
		bool bIsVisible = LightComponent->GetVisibleFlag();
		LightComponent->SetVisibility(!bIsVisible);
	}
	else {
		GameUtils::LogMessage("LightSwitch.cpp: PointLightComponent is Null");
	}


}
