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
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Abilities|Basic", ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Abilities|Basic", ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Abilities|Basic", ReplicatedUsing=OnRep_Mana)
	FGameplayAttributeData Mana;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Abilities|Basic", ReplicatedUsing=OnRep_MaxMana)
	FGameplayAttributeData MaxMana;

public:
	UAuraAttributeSet();
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

private:
	FEffectProperties EffectProperties;
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
};
