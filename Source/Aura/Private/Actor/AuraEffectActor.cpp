// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Ability/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffect(AActor* TargetActor, const TSubclassOf<UGameplayEffect> EffectClass)
{
	if (const auto ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
	{
		auto Context = ASC->MakeEffectContext();
		Context.AddSourceObject(this);

		const auto Spec = ASC->MakeOutgoingSpec(EffectClass, 1.0f, Context);
		ASC->ApplyGameplayEffectSpecToSelf(*Spec.Data);
	}
}
