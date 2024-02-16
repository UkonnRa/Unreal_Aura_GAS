// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AuraEnemy.h"

#include "Ability/AuraAbilitySystemComponent.h"
#include "Ability/AuraAttributeSet.h"

constexpr int32 GHighlightDepthRed = 250;

// Sets default values
AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityInfo();
}

void AAuraEnemy::Highlight()
{
	bIsHighlighting = true;

	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(GHighlightDepthRed);

	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(GHighlightDepthRed);
}

void AAuraEnemy::UnHighlight()
{
	bIsHighlighting = false;

	Weapon->SetRenderCustomDepth(false);
	Weapon->SetCustomDepthStencilValue(0);

	GetMesh()->SetRenderCustomDepth(false);
	GetMesh()->SetCustomDepthStencilValue(0);
}

void AAuraEnemy::InitAbilityInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	if (const auto ASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
	{
		ASC->AbilityActorInfoSet();
	}
}

int32 AAuraEnemy::GetPlayerLevel()
{
	return Level;
}
