// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;
/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()

public:
	AAuraEffectActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Applied Effects")
	TSubclassOf<UGameplayEffect> InstantEffectClass;

	UFUNCTION(BlueprintCallable)
	void ApplyEffect(AActor* TargetActor, TSubclassOf<UGameplayEffect> EffectClass);
};
