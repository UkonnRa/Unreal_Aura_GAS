// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AuraEnemy.h"

constexpr int32 GHighlightDepthRed = 250;

// Sets default values
AAuraEnemy::AAuraEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AAuraEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
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
