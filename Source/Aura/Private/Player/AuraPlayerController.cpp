// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(InputMappingContext);

	const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(InputMappingContext, 0);


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
