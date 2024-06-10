// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHud.generated.h"


class UCanvasPanel;
class USizeBox;
/**
 * 
 */
UCLASS()
class HORRORGAMEPLUGIN_API UMainHud : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;
public:


	
};
