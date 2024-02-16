// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> SourceASC;

	UPROPERTY()
	TObjectPtr<AActor> SourceAvatarActor;

	UPROPERTY()
	TObjectPtr<AController> SourceController;

	UPROPERTY()
	TObjectPtr<ACharacter> SourceCharacter;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> TargetASC;

	UPROPERTY()
	TObjectPtr<AActor> TargetAvatarActor;

	UPROPERTY()
	TObjectPtr<AController> TargetController;

	UPROPERTY()
	TObjectPtr<ACharacter> TargetCharacter;

	FEffectProperties() = default;

	explicit FEffectProperties(const FGameplayEffectModCallbackData& Data)
	{
		EffectContextHandle = Data.EffectSpec.GetContext();
		SourceASC = EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

		if (IsValid(SourceASC) && SourceASC->AbilityActorInfo.IsValid())
		{
			SourceAvatarActor = SourceASC->GetAvatarActor();
			SourceController = SourceASC->AbilityActorInfo.Get()->PlayerController.Get();
			if (SourceController == nullptr && SourceAvatarActor != nullptr)
			{
				if (const auto Pawn = Cast<APawn>(SourceAvatarActor))
				{
					SourceController = Pawn->Controller;
				}
			}
		}

		if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
		{
			const auto ActorInfo = Data.Target.AbilityActorInfo;
			TargetAvatarActor = ActorInfo->AvatarActor.Get();
			TargetCharacter = Cast<ACharacter>(TargetAvatarActor);
			TargetController = ActorInfo->PlayerController.Get();
			TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetAvatarActor);
		}
	}
};

UCLASS(BlueprintType)
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:
	/**
	 * Basic Attributes
	 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Abilities|Basic", ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Abilities|Basic", ReplicatedUsing=OnRep_Mana)
	FGameplayAttributeData Mana;

	/**
	 * Primary Attributes
	 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Abilities|Primary", ReplicatedUsing=OnRep_Strength)
	FGameplayAttributeData Strength;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Abilities|Primary", ReplicatedUsing=OnRep_Intelligence)
	FGameplayAttributeData Intelligence;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Abilities|Primary", ReplicatedUsing=OnRep_Resilience)
	FGameplayAttributeData Resilience;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Abilities|Primary", ReplicatedUsing=OnRep_Vigor)
	FGameplayAttributeData Vigor;

	/**
	 * Secondary Attributes
	 */

	// 6 + 0.25 * (Res + 2)
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Abilities|Secondary", ReplicatedUsing=OnRep_Armor)
	FGameplayAttributeData Armor;

	// 3 + 0.15 * (Res + 1)
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Abilities|Secondary",
		ReplicatedUsing=OnRep_ArmorPenetration)
	FGameplayAttributeData ArmorPenetration;

	// 4 + 0.25 * Armor
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Abilities|Secondary", ReplicatedUsing=OnRep_BlockChance)
	FGameplayAttributeData BlockChance;

	// 2 + 0.75 * (Armor + 5)
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Abilities|Secondary",
		ReplicatedUsing=OnRep_CriticalHitChance)
	FGameplayAttributeData CriticalHitChance;

	// 5 + 1.5 * ArmorPenetration
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Abilities|Secondary",
		ReplicatedUsing=OnRep_CriticalHitDamage)
	FGameplayAttributeData CriticalHitDamage;

	// 10 + 0.75 * Armor
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Abilities|Secondary",
		ReplicatedUsing=OnRep_CriticalHitResistance)
	FGameplayAttributeData CriticalHitResistance;

	// 1 + 0.1 * Vigor
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Abilities|Secondary",
		ReplicatedUsing=OnRep_HealthRegeneration)
	FGameplayAttributeData HealthRegeneration;

	// 1 + 0.1 * Int
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Abilities|Secondary",
		ReplicatedUsing=OnRep_ManaRegeneration)
	FGameplayAttributeData ManaRegeneration;

	// 80 + 2.5 * Vigor
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Abilities|Secondary", ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;

	// 50 + 2 * Int
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Abilities|Secondary", ReplicatedUsing=OnRep_MaxMana)
	FGameplayAttributeData MaxMana;

public:
	UAuraAttributeSet();

	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);

	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);

	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

private:
	FEffectProperties EffectProperties;

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue) const;


	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldValue) const;


	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue) const;
};
