// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/ModMagClac/MMC_MaxMana.h"

#include "Ability/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDefinition.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligenceDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDefinition.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligenceDefinition);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const auto SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const auto TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Intelligence = 0.0f;
	GetCapturedAttributeMagnitude(IntelligenceDefinition, Spec, EvaluateParameters, Intelligence);
	Intelligence = FMath::Max(Intelligence, 0.0f);

	float PlayerLevel = 0.0f;
	if (const auto CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject()))
	{
		PlayerLevel = CombatInterface->GetPlayerLevel();
	}

	return 50.0f + 2.5f * Intelligence + 15.0f * PlayerLevel;
}
