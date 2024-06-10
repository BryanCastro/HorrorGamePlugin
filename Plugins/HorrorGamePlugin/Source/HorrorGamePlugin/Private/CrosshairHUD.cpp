// Fill out your copyright notice in the Description page of Project Settings.


#include "CrosshairHUD.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"

void UCrosshairHUD::NativePreConstruct() {

	Super::NativePreConstruct();

	if (SizeBox) {

		SizeBox->SetWidthOverride(5.0f);
		SizeBox->SetHeightOverride(5.0f);
	}

}