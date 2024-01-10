// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AuraHUD.h"

#include "Ability/AuraAbilitySystemComponent.h"
#include "Blueprint/UserWidget.h"
#include "Characters/AuraCharacter.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/AuraOverlayWidgetController.h"
#include "UI/Widget/AuraUserWidget.h"

void AAuraHUD::InitOverlayWidget()
{
	if (const auto World = GetWorld(); World && OverlayWidget == nullptr)
	{
		OverlayWidget = CreateWidget<UAuraUserWidget>(World, OverlayWidgetClass);
		InitOverlayController();
		OverlayWidget->AddToViewport();
	}
}

UAuraOverlayWidgetController* AAuraHUD::GetOverlayController()
{
	if (OverlayWidgetController == nullptr)
	{
		InitOverlayController();
	}

	return OverlayWidgetController;
}

void AAuraHUD::InitOverlayController()
{
	checkf(OverlayWidgetControllerClass != nullptr, TEXT("OverlayWidgetControllerClass is not assigned in HUD BP"));

	if (const auto Player = Cast<AAuraCharacter>(GetOwningPawn()))
	{
		const auto PlayerController = Cast<AAuraPlayerController>(Player->GetController());
		const auto PlayerState = Cast<AAuraPlayerState>(Player->GetPlayerState());
		if (!PlayerController || !PlayerState)
		{
			return;
		}

		const auto Component = Cast<UAuraAbilitySystemComponent>(PlayerState->GetAbilitySystemComponent());

		if (const auto AttributeSet = PlayerState->GetAttributeSet(); Component && AttributeSet)
		{
			OverlayWidgetController = NewObject<UAuraOverlayWidgetController>(this, OverlayWidgetControllerClass);
			OverlayWidgetController->SetParams({
				PlayerController,
				PlayerState,
				Component,
				AttributeSet
			});
			UE_LOG(LogTemp, Warning, TEXT("OverlayWidgetController Params are set"));
			OverlayWidgetController->BindAttributeCallbacks();

			OverlayWidget->SetWidgetController(OverlayWidgetController);
			UE_LOG(LogTemp, Warning, TEXT("OverlayWidget Controller is set"));


			OverlayWidgetController->BroadcastInitialValues();
		}
	}
}
