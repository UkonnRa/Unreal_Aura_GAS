// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AuraOverlayWidgetController.h"

#include "Ability/AuraAbilitySystemComponent.h"
#include "Ability/AuraAttributeSet.h"

void UAuraOverlayWidgetController::BroadcastInitialValues()
{
	if (const auto Set = Cast<UAuraAttributeSet>(AttributeSet))
	{
		OnHealthChanged.Broadcast(Set->GetHealth());
		OnMaxHealthChanged.Broadcast(Set->GetMaxHealth());
		OnManaChanged.Broadcast(Set->GetMana());
		OnMaxManaChanged.Broadcast(Set->GetMaxMana());
	}
}

void UAuraOverlayWidgetController::BindAttributeCallbacks()
{
	if (const auto Set = Cast<UAuraAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Set->GetHealthAttribute())
		                      .AddUObject(this, &UAuraOverlayWidgetController::OnHealthAttributeChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Set->GetMaxHealthAttribute())
		                      .AddUObject(this, &UAuraOverlayWidgetController::OnMaxHealthAttributeChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Set->GetManaAttribute())
		                      .AddUObject(this, &UAuraOverlayWidgetController::OnManaAttributeChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Set->GetMaxManaAttribute())
		                      .AddUObject(this, &UAuraOverlayWidgetController::OnMaxManaAttributeChanged);
	}
}

void UAuraOverlayWidgetController::OnHealthAttributeChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UAuraOverlayWidgetController::OnMaxHealthAttributeChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UAuraOverlayWidgetController::OnManaAttributeChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UAuraOverlayWidgetController::OnMaxManaAttributeChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
