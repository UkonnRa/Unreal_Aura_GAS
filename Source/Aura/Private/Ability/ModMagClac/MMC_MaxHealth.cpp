// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/ModMagClac/MMC_MaxHealth.h"

#include "Ability/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigorDefinition.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	VigorDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDefinition.bSnapshot = false;
	
	RelevantAttributesToCapture.Add(VigorDefinition);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Vigor = 0.0f;
	GetCapturedAttributeMagnitude(VigorDefinition, Spec, EvaluateParameters, Vigor);
	Vigor = FMath::Max(Vigor, 0.0f);

	float PlayerLevel = 0;
	if (const auto CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject()))
	{
		PlayerLevel = CombatInterface->GetPlayerLevel();
	}

	return 80.0f + 2.5f * Vigor + 10.0f * PlayerLevel;
}
