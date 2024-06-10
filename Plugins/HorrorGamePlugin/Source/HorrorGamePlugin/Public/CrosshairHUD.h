// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CrosshairHUD.generated.h"

class UCanvasPanel;
class USizeBox;
class UImage;
/**
 * 
 */
UCLASS()
class HORRORGAMEPLUGIN_API UCrosshairHUD : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativePreConstruct() override;
public:
	
	UPROPERTY(meta=(BindWidget))
	USizeBox* SizeBox;

	UPROPERTY(meta=(BindWidget))
	UImage* Image;
};
