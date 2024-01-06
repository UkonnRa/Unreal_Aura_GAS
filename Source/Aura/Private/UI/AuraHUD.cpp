// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AuraHUD.h"

#include "Ability/AuraAbilitySystemComponent.h"
#include "Blueprint/UserWidget.h"
#include "Characters/AuraCharacter.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/AuraOverlayWidgetController.h"
#include "UI/Widget/AuraUserWidget.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	if (const auto World = GetWorld())
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
	OverlayWidgetController = NewObject<UAuraOverlayWidgetController>(this, OverlayWidgetControllerClass);

	if (const auto Player = Cast<AAuraCharacter>(GetOwningPawn()))
	{
		const auto PlayerController = Cast<AAuraPlayerController>(Player->GetController());
		const auto PlayerState = Cast<AAuraPlayerState>(Player->GetPlayerState());
		const auto Component = Cast<UAuraAbilitySystemComponent>(PlayerState->GetAbilitySystemComponent());

		if (const auto AttributeSet = PlayerState->GetAttributeSet(); PlayerController && PlayerState && Component &&
			AttributeSet)
		{
			OverlayWidgetController->SetParams({
				PlayerController,
				PlayerState,
				Component,
				AttributeSet
			});
			UE_LOG(LogTemp, Warning, TEXT("OverlayWidgetController Params are set"));

			OverlayWidget->SetWidgetController(OverlayWidgetController);
			UE_LOG(LogTemp, Warning, TEXT("OverlayWidget Controller is set"));
		}
	}
}
