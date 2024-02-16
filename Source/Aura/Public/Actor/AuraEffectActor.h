// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
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

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Applied Effects")
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> InfiniteTargetASCs;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	float ActorLevel = 1.0f;

	UFUNCTION(BlueprintCallable)
	void ApplyEffect(AActor* TargetActor, TSubclassOf<UGameplayEffect> EffectClass);

	UFUNCTION(BlueprintCallable)
	void RemoveEffect(AActor* TargetActor);
};
