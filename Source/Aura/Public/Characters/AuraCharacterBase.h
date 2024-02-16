// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = Combat)
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability)
	TObjectPtr<UAttributeSet> AttributeSet;

public:
	// Sets default values for this character's properties
	AAuraCharacterBase();

protected:
	virtual void BeginPlay() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void InitAbilityInfo();

	UAttributeSet* GetAttributeSet() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Attributes)
	TSubclassOf<UGameplayEffect> DefaultPrimaryEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Attributes)
	TSubclassOf<UGameplayEffect> DefaultSecondaryEffectClass;
	
	void InitializeAttributes() const;

private:
	void InitializeAttributeEffect(const TSubclassOf<UGameplayEffect> EffectClass) const;
};
