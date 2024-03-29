﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraWidgetController;
class UAuraOverlayWidgetController;
class UAuraUserWidget;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> OverlayWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAuraOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAuraWidgetController> OverlayWidgetControllerClass;

public:
	void InitOverlayWidget();

	UFUNCTION(BlueprintCallable)
	UAuraOverlayWidgetController* GetOverlayController();

private:
	void InitOverlayController();
};
