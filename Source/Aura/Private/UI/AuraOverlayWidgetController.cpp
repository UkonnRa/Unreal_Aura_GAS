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
		                      .AddLambda([this](const FOnAttributeChangeData& Data)
		                      {
			                      OnHealthChanged.Broadcast(Data.NewValue);
		                      });
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Set->GetMaxHealthAttribute())
		                      .AddLambda([this](const FOnAttributeChangeData& Data)
		                      {
			                      OnMaxHealthChanged.Broadcast(Data.NewValue);
		                      });
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Set->GetManaAttribute())
		                      .AddLambda([this](const FOnAttributeChangeData& Data)
		                      {
			                      OnManaChanged.Broadcast(Data.NewValue);
		                      });
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Set->GetMaxManaAttribute())
		                      .AddLambda([this](const FOnAttributeChangeData& Data)
		                      {
			                      OnMaxManaChanged.Broadcast(Data.NewValue);
		                      });
	}

	AbilitySystemComponent->AssetTags.AddLambda([this](const auto AssetTags)
	{
		const auto MessagesTag = FGameplayTag::RequestGameplayTag(FName("Messages"), true);
		for (const FGameplayTag& Tag : AssetTags)
		{
			if (Tag.MatchesTag(MessagesTag))
			{
				const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
				MessageWidgetRowDelegate.Broadcast(*Row);
			}
		}
	});
}

template <typename T>
T* UAuraOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
