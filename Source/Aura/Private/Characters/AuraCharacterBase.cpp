// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AuraCharacterBase.h"

#include "AbilitySystemComponent.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), "WeaponHandSocket");
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraCharacterBase::InitAbilityInfo()
{
}

UAttributeSet* AAuraCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

void AAuraCharacterBase::InitializeAttributes() const
{
	InitializeAttributeEffect(DefaultPrimaryEffectClass);
	InitializeAttributeEffect(DefaultSecondaryEffectClass);
}

void AAuraCharacterBase::InitializeAttributeEffect(const TSubclassOf<UGameplayEffect> EffectClass) const
{
	if (const auto ASC = GetAbilitySystemComponent(); IsValid(EffectClass))
	{
		const auto ContextHandle = ASC->MakeEffectContext();
		const auto SpecHandle = ASC->MakeOutgoingSpec(EffectClass, 1.0f, ContextHandle);
		GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), ASC);
	}
}
