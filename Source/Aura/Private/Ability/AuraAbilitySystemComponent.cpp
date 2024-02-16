// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec,
                                                FActiveGameplayEffectHandle EffectHandle)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 8.0f, FColor::Blue, FString("Effect Applied"));
}
