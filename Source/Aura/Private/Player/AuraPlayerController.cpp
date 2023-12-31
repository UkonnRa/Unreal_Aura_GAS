﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/HighlightInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(InputMappingContext);

	if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}


	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	const auto EnhancedInput = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::Move(const FInputActionValue& Value)
{
	// TODO: Need to understand this part
	const auto Delta = Value.Get<FVector2D>();

	const auto Matrix = FRotationMatrix({0.0f, ControlRotation.Yaw, 0.0f});
	const auto ForwardDirection = Matrix.GetUnitAxis(EAxis::X);
	const auto RightDirection = Matrix.GetUnitAxis(EAxis::Y);

	if (const auto PawnValue = GetPawn())
	{
		PawnValue->AddMovementInput(ForwardDirection, Delta.Y);
		PawnValue->AddMovementInput(RightDirection, Delta.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	if (CursorHit.bBlockingHit)
	{
		const auto HitActor = Cast<IHighlightInterface>(CursorHit.GetActor());
		LastHitActor = CurrentHitActor;
		CurrentHitActor = HitActor;

		if (CurrentHitActor && LastHitActor != CurrentHitActor)
		{
			CurrentHitActor->Highlight();
		}

		if (LastHitActor && LastHitActor != CurrentHitActor)
		{
			LastHitActor->UnHighlight();
		}
	}
}
