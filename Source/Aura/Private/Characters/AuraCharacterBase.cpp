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

void AAuraCharacterBase::InitializePrimaryAttributes() const
{
	if (const auto ASC = GetAbilitySystemComponent(); IsValid(DefaultPrimaryEffectClass))
	{
		const auto ContextHandle = ASC->MakeEffectContext();
		const auto SpecHandle = ASC->MakeOutgoingSpec(DefaultPrimaryEffectClass, 1.0f, ContextHandle);
		GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), ASC);
	}
}
