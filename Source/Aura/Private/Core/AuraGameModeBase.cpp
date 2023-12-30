// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AuraGameModeBase.h"

#include "Characters/AuraCharacter.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"

AAuraGameModeBase::AAuraGameModeBase()
{
	DefaultPawnClass = TSubclassOf<AAuraCharacter>();
	PlayerControllerClass = TSubclassOf<AAuraPlayerController>();
	PlayerStateClass = TSubclassOf<AAuraPlayerState>();
}
