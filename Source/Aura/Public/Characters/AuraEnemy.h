// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AuraCharacterBase.h"
#include "Interaction/HighlightInterface.h"
#include "AuraEnemy.generated.h"

UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IHighlightInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	bool bIsHighlighting;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Default")
	int32 Level = 1;

public:
	// Sets default values for this character's properties
	AAuraEnemy();
	
	virtual int32 GetPlayerLevel() override;
	
protected:
	virtual void BeginPlay() override;

	virtual void Highlight() override;

	virtual void UnHighlight() override;

	virtual void InitAbilityInfo() override;
};
