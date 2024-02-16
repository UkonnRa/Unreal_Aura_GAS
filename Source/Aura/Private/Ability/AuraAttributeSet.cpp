// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/AuraAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(50.0f);
	InitMaxHealth(100.0f);

	InitMana(75.0f);
	InitMaxMana(100.0f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	else if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	EffectProperties = FEffectProperties(Data);

	UE_LOG(LogTemp, Warning, TEXT("Effect Properties: %s"), *EffectProperties.EffectContextHandle.ToString());
	UE_LOG(LogTemp, Warning, TEXT("  Target ASC: %s"), *EffectProperties.TargetASC.GetName());
	UE_LOG(LogTemp, Warning, TEXT("  Target Avatar Name: %s"), *EffectProperties.TargetAvatarActor.GetName());
	UE_LOG(LogTemp, Warning, TEXT("  Target Controller: %s"), *EffectProperties.TargetController.GetName());
	UE_LOG(LogTemp, Warning, TEXT("  Target Avatar Actor: %s"), *EffectProperties.TargetAvatarActor.GetName());

	UE_LOG(LogTemp, Warning, TEXT("=== ==="));
	UE_LOG(LogTemp, Warning, TEXT("  Source ASC: %s"), *EffectProperties.SourceASC.GetName());
	UE_LOG(LogTemp, Warning, TEXT("  Source Avatar Name: %s"), *EffectProperties.SourceAvatarActor.GetName());
	UE_LOG(LogTemp, Warning, TEXT("  Source Controller: %s"), *EffectProperties.SourceController.GetName());
	UE_LOG(LogTemp, Warning, TEXT("  Source Avatar Actor: %s"), *EffectProperties.SourceAvatarActor.GetName());
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}
