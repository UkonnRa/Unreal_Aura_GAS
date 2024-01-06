// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AuraWidgetController.generated.h"

class UAuraAbilitySystemComponent;
class AAuraPlayerState;
class AAuraPlayerController;
class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FAuraWidgetControllerParams
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TObjectPtr<AAuraPlayerController> PlayerController;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TObjectPtr<AAuraPlayerState> PlayerState;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet;

	FAuraWidgetControllerParams(AAuraPlayerController* PlayerController,
	                            AAuraPlayerState* PlayerState,
	                            UAuraAbilitySystemComponent* AbilitySystemComponent,
	                            UAttributeSet* AttributeSet)
		: PlayerController(PlayerController),
		  PlayerState(PlayerState),
		  AbilitySystemComponent(AbilitySystemComponent),
		  AttributeSet(AttributeSet)
	{
	}

	FAuraWidgetControllerParams() = default;
};


UCLASS(Abstract)
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TObjectPtr<AAuraPlayerController> PlayerController;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TObjectPtr<AAuraPlayerState> PlayerState;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TObjectPtr<UAttributeSet> AttributeSet;

public:
	UFUNCTION(BlueprintCallable)
	void SetParams(const FAuraWidgetControllerParams& Params);

	virtual void BroadcastInitialValues();

	virtual void BindAttributeCallbacks();
};
