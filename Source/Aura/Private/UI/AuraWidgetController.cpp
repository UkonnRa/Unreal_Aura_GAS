// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AuraWidgetController.h"

void UAuraWidgetController::SetParams(const FAuraWidgetControllerParams& Params)
{
	PlayerController = Params.PlayerController;
	PlayerState = Params.PlayerState;
	AbilitySystemComponent = Params.AbilitySystemComponent;
	AttributeSet = Params.AttributeSet;
}

void UAuraWidgetController::BroadcastInitialValues()
{
}

void UAuraWidgetController::BindAttributeCallbacks()
{
}
